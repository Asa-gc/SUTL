import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id:idItemRoot
    property alias curState: idSex.curState
    property alias name: idTextName.text
    property alias font: idTextName.font
    property int namePixelSize:14
    property int statesNum :2
    property alias switchWidth: idSex.switchWidth
    property alias slidercamSize: idSex.slidercamSize
    property double ratioOfSwitch: 0.7  //ratioOfCombox=idSewl.width/idItemRoot.width

    signal sigSwitchClicked(int _index);

    clip: true
    Text {
        id: idTextName
        text: "Switch:"
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
    SwitchEx{
        id:idSex
        statesNum:idItemRoot.statesNum
        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        width: idItemRoot.width*ratioOfSwitch
        onSigSwitchClicked: idItemRoot.sigSwitchClicked(_index)
    }
}
