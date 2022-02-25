import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id:idItemRoot
    property alias curState: idSex.curState
    property alias switchWidth: idSex.switchWidth
    property alias slidercamSize: idSex.slidercamSize
    property var statesList:["关","开"]
    property int textPixelSize:12

    signal sigSwitchClicked(int _index);
    signal sigSwitchClickedWithLabel(int _index,string _label);
    function moveSlidercamEx(_idx){
        idSex.moveSlidercamEx((_idx));
    }
    Row{
        id:idRowLabels
        clip: true
        anchors{
            top: parent.top
            left:parent.left
            right: parent.right
        }
        height: textPixelSize+2
        Repeater{
            id:idRep
            model: statesList.length
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                id: name
                text:statesList[index]
                font.pixelSize: textPixelSize
                property int idx:index
                anchors.top: idRowLabels.top
                anchors.bottom: idRowLabels.bottom
                width:idItemRoot.switchWidth
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                clip: true
            }
        }
    }
    SwitchEx{
        id: idSex
        statesNum:statesList.length
        anchors{
            top: idRowLabels.bottom
            left:parent.left
            right: parent.right
            bottom: parent.bottom
        }
        onSigSwitchClicked: {
            idItemRoot.sigSwitchClicked(_index)
            idItemRoot.sigSwitchClickedWithLabel(_index, (_index<0||_index>=statesList.length)?
                                                 "":statesList[_index]);
        }
    }
}
