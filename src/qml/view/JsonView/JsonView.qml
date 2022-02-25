import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../../func/MyJson/MyJson.js"as MyJson

Rectangle {
//    border.color: "#000000"
//    border.width: 2
    id:idRecRoot;
    color: "#00000000"
    property Component jsonNodeComponent:null;
    property int pointSize:10
    property bool readOnly:false
    property string curJsonStr;

    signal jsonChange();
    signal jsonChangeWithAbsKey(string _absoluteKey,string _value,int _type);

    onPointSizeChanged: {
        //setJsonStr(curJsonStr);
        if(null!==idRecJsonView.rootNode){
            idRecJsonView.rootNode.setPointSize(pointSize);
        }
    }

    function getJsonObj(){
        if(null!==idRecJsonView.rootNode){
            var json=idRecJsonView.rootNode.getJsonObj()
            if(undefined!==json){
                return Object.values(json)[0];
            }
            return ;
        }
    }
    function getJsonStr(){
        return JSON.stringify(idRecRoot.getJsonObj());
    }

    function setJsonStr(_jsonStr){
        var jsonObj;
        try {
            jsonObj = JSON.parse(_jsonStr);
        }catch(e){
            console.log("jsonview",e.name, e.message,_jsonStr);
            return;
        }
        curJsonStr=_jsonStr;
        if(null===jsonNodeComponent){
            jsonNodeComponent=Qt.createComponent("./JsonNode.qml");
        }
        if(idRecRoot.jsonNodeComponent.status!==Component.Ready){
            console.log("idRecRoot.jsonNodeComponent not ready" );
            return;
        }
        if(idRecJsonView.rootNode){
            idRecJsonView.rootNode.destroyTheNode();
        }
        idRecJsonView.rootNode=idRecRoot.createObjectNode(idRecJsonView,"",jsonObj);
      }
    function setJson(_json){
        curJsonStr=JSON.stringify(_json);
        if(null===jsonNodeComponent){
            jsonNodeComponent=Qt.createComponent("./JsonNode.qml");
        }
        if(idRecRoot.jsonNodeComponent.status!==Component.Ready){
            console.log("idRecRoot.jsonNodeComponent not ready" );
            return;
        }
        if(idRecJsonView.rootNode){
            idRecJsonView.rootNode.destroyTheNode();
        }
        idRecJsonView.rootNode=idRecRoot.createObjectNode(idRecJsonView,"",_json);
      }

    //add 20211119 GC
    function setJsonWithCareKey(_json,_keyList /*Object*/ /*Array*/){
        var dstJson={};
        var dstJsonStr="";
        if(MyJson.typeObj(_keyList==="array")){
            for(let i in _keyList){
                let key=_keyList[i.toString()]
                let value=_json[key];
                if(value===undefined){
                    console.log(key, " not finded in Jsonstr!");
                    continue;
                }
                dstJson[key]=value;
            }
            dstJsonStr=JSON.stringify(dstJson);
            console.log("dstJsonStr ",dstJsonStr);
        }else{
           dstJsonStr=_jsonStr;
           console.log("_keyList is not array set all _jsonStr to view!")
        }
        idRecRoot.setJsonStr(dstJsonStr);
      }
    function setJsonStrWithCareKey(_jsonStr,_keyList){
        var srcJson;
        try {
            srcJson = JSON.parse(_jsonStr);
        }catch(e){
            console.log("jsonview",e.name, e.message);
            return;
        }
        setJsonWithCareKey(srcJson,_keyList)
      }

    function createItem(_parentItem){
        var p=_parentItem.idCLt===undefined?_parentItem:_parentItem.idCLt;
        var item=jsonNodeComponent.createObject(p,{"pointSize":pointSize,
                                                    "readOnly":readOnly});
        item.sigValueChange.connect(idRecRoot.jsonChange);
        item.sigValueChangeWithAbsKey.connect(_parentItem.childNodeValueChanged);
        return item;
    }
    /*back up 20211125
    function createItem(_parentItem){
        var p=_parentItem.idCLt===undefined?_parentItem:_parentItem.idCLt;
        var item=jsonNodeComponent.createObject(p,{"pointSize":pointSize});
        item.sigValueChange.connect(jsonChange);
        return item;
    }
    */

    function createObjectNode(_rootItem,_key,_json){
        var curNode=createItem(_rootItem);
        curNode.key=_key
        if(_key===""){
            curNode.keyVisiable=false
            curNode.symbolVisiable=false
        }
        curNode.valueVisiable=false;
        curNode.type=3;
        let keys=Object.keys(_json);
        let values=Object.values(_json);
        let length=values.length;
        let valueType="";
        let curChildNode=null;
        for(let i=0;i<length;++i){
            valueType=MyJson.typeObj(values[i])
            if("object"===valueType){
                //console.log("createObjectNode",_key,keys[i],values[i]);
                curChildNode=createObjectNode(curNode,keys[i],values[i])
            }else if("array"===valueType){
                //console.log("createObjectNode",_key,keys[i],values[i]);
                curChildNode=createArrayNode(curNode,keys[i],values[i])
            }else{//leaf node
                //console.log("createObjectNode",_key,keys[i],values[i]);
                curChildNode=createLeafNode(curNode,keys[i],values[i])
            }
            if(null===curChildNode){
                //console.log("Create child node error!",_key,valueType)
                return null;
            }
        }
        return curNode;
    }

    function createArrayNode(_rootItem,_key,_array){
        var curNode=createItem(_rootItem);
        curNode.key=_key
        curNode.valueVisiable=false;
        curNode.type=4;
        let keys=Object.keys(_array);
        let values=Object.values(_array);
        let length=values.length;
        let valueType="";
        let curChildNode=null;
        for(let i=0;i<length;++i){
            valueType=MyJson.typeObj(values[i])

            if("object"===valueType){
                //console.log("createArrayNode",_key,keys[i],values[i]);
                curChildNode=createObjectNode(curNode,keys[i],values[i])
            }else if("array"===valueType){
                //console.log("createArrayNode",_key,keys[i],values[i]);
                curChildNode=createArrayNode(curNode,keys[i],values[i])
            }else{//leaf node
                //console.log("createArrayNode",_key,keys[i],values[i]);
                curChildNode=createLeafNode(curNode,keys[i],values[i])
            }
            if(null===curChildNode){
                //console.log("Create array node error!",_key,valueType)
                return null;
            }
        }
        return curNode;
    }

    function createLeafNode(_rootItem,_key,_value){
        let type=MyJson.typeObj(_value)
        if(type!=="string"&&type!=="number"&&type!=="bool"){
            return null;
        }
        var curNode=createItem(_rootItem);
        curNode.key=_key;
        curNode.value=_value.toString();
        curNode.childNodesVisiable=false;
        if(type==="string"){
            curNode.type=0
        }else if(type==="number"){
            curNode.type=1
        }else if(type==="bool"){
            curNode.type=2
        }
        //console.log("createLeafNode",_key,_value);
        return curNode;
    }
    function refresh() {
        setJsonStr(getJsonStr())
    }
    onVisibleChanged: {
        if (visible === true) {
            refresh()
        }
    }

    ScrollView{
        id: idSvwJson
        anchors.fill: parent
        clip: true
        contentWidth: idRecJsonView.width;
        contentHeight: idRecJsonView.height
        anchors.margins: 10

        //            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        //                  ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        Rectangle{
            //border.color: "#000000"
            color: "#00000000"
            id: idRecJsonView
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
            property Item rootNode: null

            function childNodeValueChanged(_key,_value,_type){
                console.log("childNodeValueChanged Final",_key,_value)
                idRecRoot.jsonChangeWithAbsKey(_key,_value,_type);
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
