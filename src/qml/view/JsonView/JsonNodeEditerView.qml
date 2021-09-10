import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../common"

Rectangle {
    id:idRecRoot
    implicitHeight: childrenRect.height
    width: 100

    ComboWithName{
        id:idCwinType
        text: "Value Type:";
        model: ListModel{
            ListElement{
                key:"string"
            }
            ListElement{
                key:"number"
            }
            ListElement{
                key:"bool"
            }
            ListElement{
                key:"object"
            }
            ListElement{
                key:"array"
            }
        }
        anchors{
            horizontalCenter: parent.horizontalCenter;
            top: parent.top;
        }
    }
    TextwithName{
        name:"Key"
        anchors{
            horizontalCenter: idCwinType.horizontalCenter;
            top: idCwinType.bottom;

        }
    }
}
