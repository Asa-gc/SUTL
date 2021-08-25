import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
Rectangle {
    id:idRecRoot;
    property string text:"fffbbbb:";
    property int currentIndex:0;
    property int pointSize: 12;
    width: 200
    height: 20
    clip: true;
    property ListModel model: ListModel {
    }
    function append(dict){
        idRecRoot.model.append(dict)
    }
    function get(index){
        return idRecRoot.model.get(index)
    }
    function insert(index,dict){
        return idRecRoot.model.insert(index,dict)
    }
    function getCurrentIndex(){
        return currentIndex;
    }
    function setCurrentIndex(index){
        currentIndex=index;
    }
    function funcClear(){
        idComboBox.model.clear();
    }
    function getCurrentText(){
        if(undefined !== get(currentIndex) && undefined !== get(currentIndex).key){
            return get(currentIndex).key
        }else{
            return ""
        }
   }
    function getCurrentValueByKey(_key){
        if(undefined !== get(currentIndex) && undefined !== get(currentIndex)[_key]){
            return get(currentIndex)[_key]
        }else{
            return ""
        }
   }
    function setTextRole(_textRole){
        if(_textRole===undefined){
            _textRole="key"
        }
        idComboBox.textRole=_textRole
    }

    function addModelByJson(_json){//TODO 暂为单层解析,尝试修改为多层解析
        let key_list=Object.keys(_json);
        console.log(key_list)
        let value_list=Object.values(_json);
        console.log(value_list)
        let len=key_list.length;
        for(let i=0;i<len;++i){
            if(typeof(value_list[i])==="object"){
                continue;
            }
            idRecRoot.append({"key":key_list[i],"value":value_list[i]});
        }
    }


    Row {
        id: rowLayout2
        width: 200
        height: 20
        anchors.fill: parent
        spacing: 2
        Text {
            id: idLabel
            text: idRecRoot.text
            font.pointSize: pointSize
            wrapMode: Text.NoWrap
            Layout.fillWidth: false
            verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: true
            clip: true;
            fontSizeMode: Text.Fit;
        }
        ComboBox {
            id: idComboBox;
            font.pointSize: idRecRoot.pointSize
            currentIndex: idRecRoot.currentIndex;
            //Layout.maximumHeight: 20
            Layout.fillWidth: false
            textRole: "key"
            model: idRecRoot.model
            Layout.fillHeight: true
            clip: true;
            background: Rectangle {
                   radius: 3
                   border.color: "gray";
                   implicitWidth: idComboBox.width
                   implicitHeight: idComboBox.height
                   anchors.fill: parent
                   anchors.rightMargin: 3;
               }
            onCurrentIndexChanged: {
                idRecRoot.currentIndex=currentIndex;
            }
        }
        onWidthChanged: {
            rowLayout2.width=idRecRoot.width;
            idComboBox.width=idRecRoot.width*1/2;
            idLabel.width=idRecRoot.width*1/2;
        }
        onHeightChanged: {
            rowLayout2.height=idRecRoot.height;
            idComboBox.height=idRecRoot.height;
            idLabel.height=idRecRoot.height;
        }

         Component.onCompleted: {
             rowLayout2.height=idRecRoot.height;
             idComboBox.height=idRecRoot.height;
             idLabel.height=idRecRoot.height;
             rowLayout2.width=idRecRoot.width;
             idComboBox.width=idRecRoot.width*1/2;
             idLabel.width=idRecRoot.width*1/2;
         }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.33}
}
##^##*/
