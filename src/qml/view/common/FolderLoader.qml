import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import "../../../HQmlTools"

Item {
    id:idItemRoot
    property var withPathInput:true
    property alias btnTextPixeSize:idBtnOpenDialog.textPixelSize
    property alias btnText:idBtnOpenDialog.text
    property alias folder:idFdgFile.folder
    property alias currentFolder:idFdgFile.folder
    property int mode:0//0,select folder;1,select file
    property var initFolder:""
    signal sigFolderSelect(string _folderName)
    onWithPathInputChanged: {
        idTiwbFoldPath.visible=withPathInput;
        if(withPathInput===false){
            width=0
        }
    }

    height: 30
    width: 200
    Rectangle{
        id:idRecRoot
        anchors.fill: parent
        color: "#00000000"
        TextInputWithBorder{
            id:idTiwbFoldPath
            width:withPathInput?2*(idItemRoot.width/3):0
            readOnly: true
            visible: withPathInput
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            text: idItemRoot.initFolder
//            TipToolWithMouseArea{
//                text: idTiwbFoldPath.text
//            }
        }
        ButtonEx{
            id:idBtnOpenDialog
            text:"open"
            textPixelSize: 16
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: withPathInput?idTiwbFoldPath.right:parent.left
            onClicked: {
                idFdgFile.open()
            }
        }
    }
    FileDialog{
        id:idFdgFile
        selectFolder:mode===0?true:false
        onAccepted: {
            let dstStr=String(idFdgFile.fileUrl).replace("file:///","")
            console.log("accepted file/folder:",dstStr)
            idItemRoot.sigFolderSelect(dstStr)
        }
    }
    TipToolWithMouseArea{
        text: idTiwbFoldPath.text
    }
}
