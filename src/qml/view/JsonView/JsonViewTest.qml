import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TestJsonView")

   JsonView{
       id: idjvTesst;
       anchors.fill:  parent
       anchors.margins: 10
   }
   Button {
       id: button
       x: 540
       y: 0
       text: qsTr("Button")
       property int ps:5
       onClicked: {
           idjvTesst.pointSize=(ps=ps+5)
       }
   }
   Button {
       id: button1
       x: 434
       y: 0
       text: qsTr("Button")
       onClicked: {
           var jsonObj=idjvTesst.getJsonObj();
           console.log("JSON.stringify(jsonObj)",JSON.stringify(jsonObj));
       }
   }
   function onJsonChange() {
       var jsonObj=idjvTesst.getJsonObj();
       console.log("onJsonChange",JSON.stringify(jsonObj));
   }
   Component.onCompleted: {
       var json={"number":0,"string":"str","bool":0,"object":{"number":0,"string":"str","bool":1},"array":[0,"str",1]}
       idjvTesst.setJsonStr(JSON.stringify(json));
       idjvTesst.jsonChange.connect(onJsonChange);
       console.log("onCompleted",JSON.stringify(json));

   }
}
