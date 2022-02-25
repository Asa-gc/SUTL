import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id:idItemRoot
    property alias name: idTxtKey.text
    property alias value:idTiwbValue.text
    property alias readOnly: idTiwbValue.readOnly
    property alias hasBored:idTiwbValue.hasBored;
    property alias namePointSize:idTxtKey.font.pointSize
    property alias wrapMode:idTxtKey.wrapMode
    width: 200
    height: 20
    signal sigEditingFinshed(string _text);
    RowLayout {
        id: rowLayout9
        width: 127
        height: 18
        anchors.rightMargin: 0
        anchors.fill: parent
        spacing: 2
        Text {
            id: idTxtKey
            text: "Name";
            wrapMode: Text.NoWrap;
            anchors.margins: 1;
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true;
        }

        TextInputWithBorder {
            id:idTiwbValue
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "value"
            Layout.margins: 1
            onSigEditingFinshed: {
                idItemRoot.sigEditingFinshed(_text);
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
