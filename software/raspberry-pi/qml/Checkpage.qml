import QtQuick
import QtQuick.Window
import QtQuick.Controls

Rectangle {
    width: 1280
    height: 800
    property int chbut_width: 100
    property int chbut_heigth: 100
    Image {
        anchors.fill: parent
        source: "UI_2.1/p3/images/background.png"
    }
    Button {
        id: check_frame
        width: 500
        height: 633
//        anchors.top: parent.top
        y:5
//        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        background: Image {
            source: "UI_2.1/p3/images/Page3_03.png"
        }
        rotation: 90
    }
    Row {
        id: buts_check
        spacing: 60
//        anchors.top: check_frame.bottom
//        anchors.topMargin: 20
        y:600
        anchors.horizontalCenter: check_frame.horizontalCenter

        Button {
            id: check_but
            width: chbut_width
            height: chbut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p3/images/Page3_08.png"
            }
        }
        Button {
            id: check_main
            width: chbut_width
            height: chbut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p3/images/Page3_07.png"
            }
            onClicked: {
                myloader.sourceComponent = page_main
            }
        }
    }
}

