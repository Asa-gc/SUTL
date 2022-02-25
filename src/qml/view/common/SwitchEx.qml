import QtQuick 2.0
import QtQuick.Controls 2.12
Item {
    id:idItemRoot
    property int curState : 0
    property int slidercamSize : 10
    property int statesNum :3
    property int switchWidth: idItemRoot.width/statesNum
    signal sigSwitchClicked(int _index);

    function moveSlidercam(_obj){
        let x=_obj.x
        let w=_obj.width
        idRecSlidercam.dstX=x+(w-idRecSlidercam.width)/2
        idRecSlidercam.flag=true
    }
    function moveSlidercamEx(_idx){
        let tobj=idRep.itemAt(curState)
        let x=tobj.x
        let w=tobj.width
        idRecSlidercam.dstX=x+(w-idRecSlidercam.width)/2
        idRecSlidercam.flag=true
    }
    Rectangle{
        id:idRecslider
        anchors.fill: parent
        anchors.topMargin: parent.height/3
        anchors.bottomMargin: parent.height/3
        anchors.leftMargin: switchWidth/2-idItemRoot.slidercamSize-2
        anchors.rightMargin:switchWidth/2-idItemRoot.slidercamSize
        color: "white"
        border.color: "gray"
        radius: parent.height/6
    }

    Rectangle{
        id:idRecSlidercam
        width: idItemRoot.slidercamSize*2
        height: idItemRoot.slidercamSize*2
        radius: idItemRoot.slidercamSize
        color: "skyblue"
        x:(switchWidth-idRecSlidercam.width)/2
        y:(idItemRoot.height-idRecSlidercam.width)/2
        property bool flag:false
        property int dstX:0
        NumberAnimation on x {
            running: idRecSlidercam.flag
            from: idRecSlidercam.x; to: idRecSlidercam.dstX
            duration: 100
            onStopped: {
                idRecSlidercam.flag=false
            }
        }
    }
    Row {
        id:idRow
        anchors.fill: parent

        Repeater{
            id:idRep
            model: statesNum
            anchors.horizontalCenter: parent.horizontalCenter
            MouseArea{
                property int idx:index
                anchors.top: idRow.top
                anchors.bottom: idRow.bottom
                width:idItemRoot.switchWidth
                onClicked: {
                    idItemRoot.sigSwitchClicked(idx);
                    idItemRoot.curState=idx
                    idItemRoot.moveSlidercam(idRow.children[idx])
                }
            }
        }
    }
    Component.onCompleted: {
        idItemRoot.moveSlidercam(idRep.itemAt(curState));
    }
}
