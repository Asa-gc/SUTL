import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../common"

Rectangle {
    id: idRecRoot
    implicitWidth: childrenRect.width+3
    implicitHeight: childrenRect.height+3
    property alias idCLt: idCLt
    property alias key: idTextKey.text
    property alias value: idTiwbValue.text
    property alias keyVisiable: idTextKey.visible
    property alias symbolVisiable: idTxtSymbol.visible
    property alias valueVisiable: idTiwbValue.visible
    property alias childNodesVisiable: idCLt.visible
    property int pointSize:15
    property bool unfoldFlag:true
    property int type:0    //0 string 1number 2 bool 3object 4array
    property int nodeWidth:20;
    objectName: "JsonNode"//mark type

    signal sigValueChange();

    onKeyVisiableChanged: {
        if(false===keyVisiable){
            idTextKey.height=0;
        }else{
            idTextKey.height=(idRecRoot.pointSize+1)*2
        }
    }
    onSymbolVisiableChanged: {
        if(false===keyVisiable){
            idTxtSymbol.height=0;
        }else{
            idTxtSymbol.height=(idRecRoot.pointSize+1)*2
        }
    }
    onValueVisiableChanged: {
        if(false===keyVisiable){
            idTiwbValue.height=0;
        }else{
            idTiwbValue.height=(idRecRoot.pointSize+1)*2
        }
    }
    onChildNodesVisiableChanged:{
        if(false===childNodesVisiable){
            idCLt.height=0;
        }else{
            idCLt.height=idCLt.lastHeight;
        }
    }

    function getJsonObj(){
        var jsonObj={};

        switch (idRecRoot.type){
        case 0:
            jsonObj[idRecRoot.key]=idRecRoot.value;
            return jsonObj;
        case 1:
            jsonObj[idRecRoot.key]=Number(idRecRoot.value);
            return jsonObj;
        case 2:
            jsonObj[idRecRoot.key]=Boolean(idRecRoot.value);
            return jsonObj;
        case 3:
            jsonObj[idRecRoot.key]=getChildNodeJsonObj();
            return jsonObj;
        case 4:
            jsonObj[idRecRoot.key]=getChildNodeJsonArray();
            return jsonObj;
        default:
            return;
        }
    }

    function getChildNodeJsonObj(){
        var childNodeJsonObj={};
        for(let index in idCLt.children){
            if("JsonNode"!==idCLt.children[index].objectName){
               continue;
            }
            let tjs=idCLt.children[index].getJsonObj()
            childNodeJsonObj[Object.keys(tjs)[0]]=Object.values(tjs)[0]
        }
        return childNodeJsonObj;
    }

    function getChildNodeJsonArray(){
        var childNodeJsonObj=[];
        for(let index in idCLt.children){
            if("JsonNode"!==idCLt.children[index].objectName){
               continue;
            }
            let tjs=idCLt.children[index].getJsonObj()
            childNodeJsonObj[index]=Object.values(tjs)[0]
        }
        return childNodeJsonObj;
    }
    function destroyTheNode(){
        destroyNodesChildren();
        idRecRoot.destroy();
    }

    function destroyNodesChildren(){
        switch (type){
        case 3:case 4:
            for(let index in idCLt.children){
                if("JsonNode"!==idCLt.children[index].objectName){
                   continue;
                }
                idCLt.children[index].destroyTheNode();
            }
            break;
        }
    }

    function setPointSize(_pointSize){
        pointSize=_pointSize;
        switch (type){
        case 3:case 4:
            for(let index in idCLt.children){
                if("JsonNode"!==idCLt.children[index].objectName){
                   continue;
                }
                idCLt.children[index].setPointSize(_pointSize);
            }
        }
    }

    function setNodeVisable(_visable){
        //set children visable
        if(false===_visable){
            idCLt.lastHeight=idCLt.height
        }
        for(let index in idCLt.children){
            if("JsonNode"!==idCLt.children[index].objectName){
               continue;
            }
            idCLt.children[index].setNodeVisable(_visable);
        }
        idRecRoot.visible=_visable;

    }
    function setChildrenVisable(_visable){
        //set children visable
        for(let index in idCLt.children){
            if("JsonNode"!==idCLt.children[index].objectName){
               continue;
            }
            idCLt.children[index].setNodeVisable(_visable);
        }
        idCLt.visible=_visable
    }

    Text {
        id: idTextKey;
        text: "key";
        style: Text.Normal
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        width: idRecRoot.pointSize*idRecRoot.nodeWidth/2
        height: (idRecRoot.pointSize+1)*2
        clip: true
        anchors{
            top: idRecRoot.top
            left: idRecRoot.left
            //margins: 3
        }
        font{
            family: "微软雅黑"
            pointSize:idTextKey.height/2-1;
        }
        color: "black"
    }
    Text {
        id:idTxtSymbol
        text: qsTr(":")
        width: contentWidth*2
        height: (idRecRoot.pointSize+1)*2
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: true
        anchors{
            verticalCenter: idTextKey.verticalCenter
            left: idTextKey.right
            //margins: 3
        }
        font{
            family: "微软雅黑"
            pointSize:idTextKey.height/2-1;
        }
        color: "black"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                switch (type){
                case 0:case 1:case 2:
                return ;
                }

                unfoldFlag=!unfoldFlag;
                if(false===unfoldFlag){
                    idCLt.lastHeight=idCLt.height
                    idRecRoot.setChildrenVisable(false)
                    idTxtSymbol.text="+";
                    return;
                }
                idRecRoot.setChildrenVisable(true)
                idTxtSymbol.text=":";
            }
        }
    }
    TextInputWithBorder{
        id: idTiwbValue
        width:idRecRoot.pointSize*idRecRoot.nodeWidth/2
        height:(idRecRoot.pointSize+1)*2
        anchors{
            verticalCenter: idTextKey.verticalCenter
            left: idTxtSymbol.right;
            margins: 2;
        }
    }
    ColumnLayout{
        id: idCLt
        property int lastHeight:0
        spacing: 0
        clip: true
        anchors{
            top: idTextKey.bottom
            left: idTextKey.left
            margins: 0
            leftMargin: 10
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
