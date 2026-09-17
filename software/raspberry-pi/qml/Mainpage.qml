import QtQuick
import QtQuick.Controls

Rectangle {
    width: 1280
    height: 800
    Image {
        id: back_main
        source: "UI_2.1/p0/images/background.png"
        anchors.fill: parent//父控件
    }

    Button {
        id: lf_design
        width: 226
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 74
        y:20
//        anchors.top: parent.top
//        anchors.topMargin: 60
        background: Image {
            source: "UI_2.1/p0/images/Page0_03.png"
        }
    }
    Button {
        id: team_name
        width: 926
        height: 450
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: lf_design.bottom
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.verticalCenterOffset: -80
        background: Image {
            source: "UI_2.1/p0/images/Page0_06.png"
        }
    }
    Row {
        id: buts
//        anchors.top: team_name.bottom
        y:520
        anchors.horizontalCenter: team_name.horizontalCenter
        spacing: 50

        Button {
            id: but_video
            width: but_width
            height: but_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p0/images/Page0_09.png"
            }
            onClicked: {
                myloader.sourceComponent = page_video
            }
        }

        Button {
            id: but_cv
            width: but_width
            height: but_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p0/images/Page0_11.png"
            }
            onClicked: {
				videoCapture.unlock()
                myloader.sourceComponent = page_cv
            }
        }

        Button {
            id: but_check
            width: but_width
            height: but_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p0/images/Page0_13.png"
            }
            onClicked: {
                myloader.sourceComponent = page_check
            }
        }

        Button {
            id: turn_off
            width: but_width
            height: but_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p0/images/Page0_16.png"
            }
            onClicked: {
                // 在这里执行关机操作
                 Qt.quit();
            }

        }
    }

//    Timer {
//        id: inactivityTimer1
//        interval: 5000 // 5秒后自动跳转
//        running: true
//        repeat: false
//        onTriggered: {
//            myloader.sourceComponent = page_video
//        }
//    }
//    MouseArea {
//        id: mouseArea1
////        anchors.fill: parent

//        onClicked: {
//            // 当有鼠标点击事件时，重置定时器
//            inactivityTimer1.restart();
//            }
//        }
}

