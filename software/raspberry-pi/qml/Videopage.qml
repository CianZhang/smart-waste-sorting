import QtQuick
import QtQuick.Controls
import QtMultimedia

Rectangle {
    width: 1280
    height: 800
    property int vibut_width: 100
    property int vibut_heigth: 100

    Image {
        source: "UI_2.1/p1/images/background.png"
        anchors.fill: parent
    }

    Rectangle {
        id: video_frame
        height: 640
        width: 1140
//        x:10
        y:10
        anchors.horizontalCenter: parent.horizontalCenter

        MediaPlayer{
            id: player
            source: "./1.mp4"
            audioOutput: audioOutput
            videoOutput: videoOutput
        }

        AudioOutput{
            id: audioOutput
            volume: volumeSlider.value
        }

        VideoOutput{
            id: videoOutput
            width: video_frame.width
            anchors.centerIn: parent
        }

        Rectangle{
            color: 'black'
            width: col.width
            height: col.height
            anchors.top: parent.top
            anchors.right: parent.right
            Column{
                id: col
                Text{
                    color: 'white'
                    text: qsTr("音量")
                }
                Slider{
                    id: volumeSlider
                    orientation: Qt.Vertical
                    value: 0.5
                    anchors.margins: 20
                }
            }
        }

        Component.onCompleted: {
            player.play()
        }

    }

    Row {
        id: buts_video
        spacing: 50
        anchors.top: video_frame.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: video_frame.horizontalCenter
        Button {
            id: video_start
            width: vibut_width
            height: vibut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {

                source: "UI_2.1/p1/images/Page1_07.png"
            }
            onClicked: {
                player.play()
            }
        }
        Button {
            id: video_pause
            width: vibut_width
            height: vibut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p1/images/Page1_09.png"
            }
            onClicked: {
                player.pause()
            }
        }
        Button {
            id: but_main
            width: vibut_width
            height: vibut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p1/images/Page1_11.png"
            }
            onClicked: {
                myloader.sourceComponent = page_main
            }
        }
    }

//    MouseArea {
//        id: mouseArea
//        anchors.fill: video_frame

//        onClicked: {
//             myloader.sourceComponent = page_cv
//        }
//    }
}
