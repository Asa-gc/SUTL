import QtQuick 2.12

Item{
    id:idItemRoot
    property alias borderRadius: idRecBorder.radius
    property alias text: idTteValue.text
    property alias inputMask: idTteValue.inputMask
    property var borderColor:"darkslategray"
    property var lastValue;
    property alias horizontalAlignment: idTteValue.horizontalAlignment
    property alias verticalAlignment: idTteValue.verticalAlignment
    property var fontFamily:"微软雅黑"
    signal sigEditingFinshed(string _text);
    width: 60
    height: 20
    function setInputMaskEx(_type,_length,_decollator){ //_type see qthelp://org.qt-project.qtquick.5132/qtwidgets/qlineedit.html#inputMask-prop/
        if(_decollator===undefined){
            _decollator=""
        }

        let mask=_type;
        for(let i=0;i<_length;++i ){
            mask+=(_decollator+_type);
        }
        idItemRoot.inputMask=mask;
    }
    Rectangle {
        id: idRecBorder
        border.color: idItemRoot.borderColor
        radius: 3;
        anchors.fill:parent;
        clip: true;
        TextInput {
            id: idTteValue
            text:""
            inputMask: ""
            anchors{fill: parent;margins: 2;}
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            selectByMouse: true
            clip:true
            font{family: idItemRoot.fontFamily;pointSize: idItemRoot.height/2-1;}
            onEditingFinished:{
                if(idItemRoot.lastValue!==idTteValue.text){
                    console.log("EditingFinished Text:",idTteValue.text)
                    sigEditingFinshed(text);
                }
            }
            onFocusChanged: {
                if(true===idTteValue.focus){
                    idItemRoot.lastValue=idTteValue.text;
                }
            }
            Keys.onEnterPressed: idTteValue.focus=false;
        }
    }
}
