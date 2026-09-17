import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    width: 1280
    height: 800
    visible: true
    title: qsTr("Main")
    minimumHeight: 800
    minimumWidth: 1280
    maximumHeight: 800
    maximumWidth: 1280
	visibility: Window.FullScreen
    property int but_width: 180
    property int but_heigth: 180
    property int count1: 0
    property int count2: 0
    property int count3: 0
    property int count4: 0
    property int count: 0

    function trash1_over(flag_red){
        if(flag_red){
            myloader.item.trash1_text="Y";
            myloader.item.trash1_color="red";
        }
        else {
            myloader.item.trash1_text="N";
            myloader.item.trash1_color="green";
        }
    }

    function trash2_over(flag_red){
        if(flag_red){
            myloader.item.trash2_text="Y";
            myloader.item.trash2_color="red";
        }
        else {
            myloader.item.trash2_text="N";
            myloader.item.trash2_color="green";
        }
    }
    function trash3_over(flag_red){
        if(flag_red){
            myloader.item.trash3_text="Y";
            myloader.item.trash3_color="red";
        }
        else {
            myloader.item.trash3_text="N";
            myloader.item.trash3_color="green";
        }
    }
    function trash4_over(flag_red){
        if(flag_red){
            myloader.item.trash4_text="Y";
            myloader.item.trash4_color="red";
        }
        else {
            myloader.item.trash4_text="N";
            myloader.item.trash4_color="green";
        }
    }


    function add_count1(){
        count1++
        myloader.item.num1_count=count1
    }

    function add_count2(){
        count2++
        myloader.item.num2_count=count2
    }
    function add_count3(){
        count3++
        myloader.item.num3_count=count3
    }
    function add_count4(){
        count4++
        myloader.item.num4_count=count4
    }
    function text_click(str_text){
        count++
        var data={
            "name": str_text,
            "numbe":count
        }

        myloader.item.data_model.append(data)
        myloader.item.data_list.incrementCurrentIndex()

    }


    function reload(){
        myloader.item.img_source=""
        myloader.item.img_source="image://mycv"
        //console.log("main.qml reload pressed")
        mycv2.changeflag_stream()

    }
    Loader {
        id: myloader
        anchors.centerIn: parent
    }
    Component.onCompleted: {
        myloader.sourceComponent = page_main
    }
    Component {
        id: page_main
        Mainpage {
            anchors.centerIn: parent
        }
    }
    Component {
        id: page_video
        Videopage {
            anchors.centerIn: parent
        }
    }
    Component {
        id: page_cv
        Cvpage {
            anchors.centerIn: parent
        }
    }

    Component {
        id: page_check
        Checkpage {
            anchors.centerIn: parent
        }
    }
        Timer {
            id: inactivityTimer
            interval: 50000 // 5秒后自动跳转
            running: true
            repeat: false
            onTriggered: {
                if (myloader.sourceComponent == page_main) {
                    inactivityTimer.restart()
                    myloader.sourceComponent = page_video
                }
//                if (myloader.sourceComponent == page_cv){
//                    inactivityTimer.restart()
//                    myloader.sourceComponent = page_video
//                }
            }
        }
}
