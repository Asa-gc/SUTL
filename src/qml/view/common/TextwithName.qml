import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle{
    id:idRecRoot;
    implicitWidth: childrenRect.width+3
    implicitHeight: childrenRect.height+3
    property alias name:idTxtName.text
    property alias symbol:idTxtSymbol.text
    property alias text:idTiwbText.text
    property int pointSize:15
    property int family:"微软雅黑"
    property int widthCoeff:20
    Text {
        id: idTxtName
        text: qsTr("name");
        style: Text.Normal
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        width: idRecRoot.pointSize*idRecRoot.widthCoeff/2
        height: (idRecRoot.pointSize+1)*2
        font{
            family: idRecRoot.family
            pointSize:idRecRoot.pointSize
        }
        clip: true
        anchors{
            left: parent.left;
            verticalCenter: parent.verticalCenter;
            margins: 3;
        }
    }
    Text {
        id: idTxtSymbol
        text: qsTr(":")
        style: Text.Normal
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        width: contentWidth*2
        height: (idRecRoot.pointSize+1)*2
        clip: true
        font{
            family: idRecRoot.family
            pointSize:idRecRoot.pointSize
        }
        anchors{
            left: idTxtName.right;
            verticalCenter: idTxtName.verticalCenter;
            margins: 3;
        }
    }
    TextInputWithBorder{
        id:idTiwbText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        width: idRecRoot.pointSize*idRecRoot.widthCoeff/2
        height: (idRecRoot.pointSize+1)*2
        clip: true
        fontFamily:idRecRoot.family
        anchors{
            left: idTxtSymbol.right;
            verticalCenter: idTxtName.verticalCenter;
            margins: 3;
        }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
