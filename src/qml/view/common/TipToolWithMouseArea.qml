import QtQuick 2.0
import QtQuick.Controls 2.12

MouseArea{
    property alias text:idTtp.text
    property alias delay:idTtp.delay
    property bool entered: false
    property bool showTip: true
    hoverEnabled: true
    anchors.fill: parent
    propagateComposedEvents: true
    onClicked: {
         mouse.accepted = false
    }

    onCanceled: {
        mouse.accepted = false
    }

    onDoubleClicked:{
        mouse.accepted = false
    }

    onPositionChanged:{
        mouse.accepted = false
    }

    onPressAndHold:{
        mouse.accepted = false
    }

    onPressed:{
        mouse.accepted = false
    }

    onReleased:{
        mouse.accepted = false
    }

    onEntered: {
        entered = true
    }

    onExited: {
        entered = false
    }

    ToolTip{
        id:idTtp
        visible: showTip?parent.entered:showTip
        text: ""
        delay: 100
    }
}
