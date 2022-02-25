import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../JsonView"
Item {
    id:idItemRoot
    property ListModel modle:ListModel{
    }
    property Component delegate:Item {
        //{"func_code":"set_json_str","args":...}
        property int currentIndex:-1;
        JsonView{
            id:idJvw
            anchors.fill: parent
            Component.onCompleted: {
                let json=args
                let jsonStr=JSON.toString(json)
                idJvw.setJsonStr(jsonStr);
                currentIndex
            }
        }
    }

//    border.color: "#000000"
//    border.width: 3
    ScrollView {
        id: idSvw
        anchors.fill: parent
        horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
        verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
        ListView{
            id:idLvw
            anchors.fill: parent
            model:idItemRoot.modle
            delegate:idItemRoot.delegate
        }
    }
}
