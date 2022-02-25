import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
Rectangle {
    id:idRecRoot;
//    border.color: "#000000"
//    border.width: 1
    property string text:"name:";
    property alias currentIndex:idComboBox.currentIndex;
    property int pointSize: 12;
    property int   namePixelSize: 12;
    property alias textRole:idComboBox.textRole
    property alias pointSize:idComboBox.font.pointSize
    property alias comboxPixelSize:idComboBox.font.pixelSize
    property double ratioOfCombox: 0.5  //ratioOfCombox=idComboBox.width/idRecRoot.width
    
    color: "#00000000"
    width: 200
    height: 25
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
        if(index<0){
            console.log("ComboWithName set a >0 index:",index,"set currentindex=0");
            currentIndex=0;
        }else if(index>=idRecRoot.model.count){
            console.log("ComboWithName set a >Max index:",index,"set currentindex=idRecRoot.model.count-1");
            currentIndex=idRecRoot.model.count-1;
        }else{
            currentIndex=index;
        }
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
    function getIndexByKey(_key){
        return idComboBox.find(_key);
    }
    function getIndexByKeyValue(_key,_value){
        if(_key===undefined||_value===undefined){
            return -1;
        }
        let size= idRecRoot.model.count;
        console.log("size",size);
        for(let i=0;i<size;++i){

            console.log(_key,"`s value",idRecRoot.model.get(i)[_key]);
            if(idRecRoot.model.get(i)[_key]===_value){
                return i;
            }
        }
    }
    function getValueByIndexKey(_index,_key){
       return  idRecRoot.model.get(_index)[_key];
    }
    function setCurrentIndexByKeyValue(_key,_value){
        setCurrentIndex(getIndexByKeyValue(_key,_value));
    }

    function addModelByJson(_json){
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


    Component{
        id:idCptEmptyIndicator
        Item {
            id: name
            width: 0
            anchors.fill: parent
            height: parent.height
        }
    }

    Item {
        id: rowLayout2
        anchors.fill: parent
       // spacing: 2
        Text {
            id: idLabel
            text: idRecRoot.text
            font.pixelSize: namePixelSize
            wrapMode: Text.NoWrap
            width: idRecRoot.width*(1-ratioOfCombox);
            verticalAlignment: Text.AlignVCenter
            clip: true;
            fontSizeMode: Text.Fit;
            anchors.fill: parent
            anchors.rightMargin: parent.width*ratioOfCombox
        }
        ComboBox {
            id: idComboBox;
            font.pointSize: 12//idRecRoot.comboxPixelSize
            currentIndex: 0;
            textRole: "key"
            width: idRecRoot.width*ratioOfCombox-10;
            model: idRecRoot.model
            clip: true;
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: idLabel.right
            indicator:Canvas {
                id: canvas
                anchors.right: parent.right
                anchors.top: parent.top
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                    margins: idComboBox.height/3
                }

                width: height
                contextType: "2d"

                Connections {
                    target: idComboBox
                    onPressedChanged: canvas.requestPaint()
                }

                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = "gray";
                    context.fill();
                }
            }

            background: Rectangle {
                   radius: 3
                   border.color: "gray";
                   implicitWidth: idComboBox.width
                   implicitHeight: idComboBox.height
                   anchors.fill: parent
//                   anchors.rightMargin: 5;
               }
            onActivated: {
                idRecRoot.sigActivated(index)
            }
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
//             rowLayout2.width=idRecRoot.width;
//             idComboBox.width=idRecRoot.width*1/2;
//             idLabel.width=idRecRoot.width*1/2;
         }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.33}
}
##^##*/
