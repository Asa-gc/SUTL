import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    id:idRecRoot;
    property string text:"key:";
    property var value:0;
    property int wrapMode: Text.NoWrap
    property bool readOnly: false

    width: 200
    height: 20
    clip: true;
    onWrapModeChanged: {
        idLable.wrapMode=wrapMode;
    }
    onClipChanged: {
        idLable.clip=clip
        idTteInSourceFre.clip=clip
    }

    onReadOnlyChanged: {
        idTteInSourceFre.readOnly=readOnly;
    }

    Row {
        id: rowLayout9
        width: 127
        height: 18
        anchors.fill: parent
        spacing: 2
        Text {
            id: idLable
            text: idRecRoot.text;
            wrapMode: Text.NoWrap;
            anchors.margins: 1;
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
            Layout.fillHeight: true
            clip: true;
        }

        TextEdit {
            id: idTteInSourceFre
            width: 100
            Layout.fillWidth: true
            anchors.margins: 0;
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            selectByMouse: true
            text:idRecRoot.value;
            readOnly: idRecRoot.readOnly
            textMargin: 2

            Rectangle {
                id: idRecBackgroud
                height: 1000
                color: "#00000000"
                border.color: "#808080"
                anchors.fill: parent
                anchors.rightMargin: 3;
                radius: 3;
            }
            onTextChanged: {
                idRecRoot.value=text;
            }
            onReadOnlyChanged: {
                if(readOnly===true){
                    idRecBackgroud.color="#aa8a8a8a"
                }else{
                    idRecBackgroud.color="#00000000"
                }
            }

            font.pointSize: 10
            Layout.fillHeight: true

        }

        onWidthChanged: {
            idTteInSourceFre.width=idRecRoot.width*1/2;
            idLable.width=idRecRoot.width*1/2;
        }
        onHeightChanged: {
            rowLayout9.height=idRecRoot.height;
            idTteInSourceFre.height=idRecRoot.height;
            idLable.height=idRecRoot.height;
        }
         Component.onCompleted: {
             rowLayout9.height=idRecRoot.height;
             idTteInSourceFre.height=idRecRoot.height;
             idLable.height=idRecRoot.height;
             rowLayout9.width=idRecRoot.width;
             idTteInSourceFre.width=idRecRoot.width*1/2;
             idLable.width=idRecRoot.width*1/2;
         }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
