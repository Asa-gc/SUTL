import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:idItemRoot
    height: 40
    width: 200
    property alias text:idBtn.text
    property var radius:5
    property var pressedColor:"lightgray"
    property var unprissedColor:"#0292AA"
    property var textPixelSize:20
    property var textColor:"white";
    property var textWeight:Font.DemiBold
    property var textFamily:"微软雅黑"
    property var borderColor:"lightgray"
    property var unenableColor:"#C1BDBD"
    property var horizontalAlignment:Text.AlignHCenter
    property var verticalAlignment: Text.AlignVCenter
    signal clicked();

    Button{
        id:idBtn
        text: ""
        anchors.fill: parent
        style:ButtonStyle{
            background: Rectangle{
                id:idRecBackgroud
                anchors.fill: parent
                color: {
                    if(idItemRoot.enabled===false){
                        return unenableColor
                    }
                    return control.pressed? idItemRoot.pressedColor:idItemRoot.unprissedColor
                }
                border.width:1;
                border.color: idItemRoot.borderColor
                radius: idItemRoot.radius
            }
            label: Item {
                anchors.fill: parent;
                Text {
                    text: idBtn.text;
                    anchors.centerIn: parent;
                    color: idItemRoot.textColor
                    font.pixelSize: idItemRoot.textPixelSize
                    font.weight: idItemRoot.textWeight
                    font.family: idItemRoot.textFamily
                    horizontalAlignment:idItemRoot.horizontalAlignment
                    verticalAlignment:idItemRoot.verticalAlignment
                }
            }
         }
        onClicked: {
            idItemRoot.clicked();
        }
    }
}
