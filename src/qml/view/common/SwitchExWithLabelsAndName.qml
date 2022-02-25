import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id:idItemRoot
    property alias curState: idSewl.curState
    property alias name: idTextName.text
    property alias font: idTextName.font
    property int namePixelSize:14
    property alias statesList: idSewl.statesList
    property alias switchWidth: idSewl.switchWidth
    property alias slidercamSize: idSewl.slidercamSize
    property alias switchTextPixelSize:idSewl.textPixelSize
    property double ratioOfSwitch: 0.7  //ratioOfCombox=idSewl.width/idItemRoot.width

    signal sigSwitchClicked(int _index);
    signal sigSwitchClickedWithLabel(int _index,string _label);
    function moveSlidercamEx(_idx){
        idSewl.moveSlidercamEx((_idx));
    }

    clip: true
    Text {
        id: idTextName
        text: "Switch"
        font.pixelSize: idItemRoot.namePixelSize
        clip: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors{
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: idItemRoot.width*(1-ratioOfSwitch)
    }
    SwitchExWithLabels{
        id:idSewl
        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        width: idItemRoot.width*ratioOfSwitch
        onSigSwitchClicked: idItemRoot.sigSwitchClicked(_index)
        onSigSwitchClickedWithLabel:
            idItemRoot.sigSwitchClickedWithLabel(_index, (_index<0||
                                                 _index>=idItemRoot.statesList.length)?
                                                 "":idItemRoot.statesList[_index])
    }
}
