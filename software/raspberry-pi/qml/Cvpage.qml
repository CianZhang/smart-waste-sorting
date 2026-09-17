import QtQuick 2.15
import QtQuick.Controls 2.0

Rectangle {
    id:rect123
    width: 1280
    height: 800
    property int cvbut_width: 100
    property int cvbut_heigth: 100
    property int myspacing: 10
    property int count: 0
    property int pointsize: 20

    property color trash1_color:"green"
    property color trash2_color:"green"
    property color trash3_color:"green"
    property color trash4_color:"green"
    property string trash1_text: "N"
    property string trash2_text: "N"
    property string trash3_text: "N"
    property string trash4_text: "N"

    property alias img_source: img_cv.source
    property alias num1_count: num1.text
    property alias num2_count: num2.text
    property alias num3_count: num3.text
    property alias num4_count: num4.text

    //property alias color1:trash1_color
    //property alias color2:trash2_color
    //property alias color3:trash3_color
    //property alias color4:trash4_color

//    property alias data_model: model
//    property alias data_list: list

    function text_clicked(){
        var data={
            "name": "banna",
            "numbe":count
        }
        model.append(data)
        list.incrementCurrentIndex()
//        inactivityTimer.restart()
    }

    Image {
        source: "UI_2.1/p2/images/background.png"
    }
    Button {
        id: rect1
        width: 300
        height: 700
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 10
        background: Image {
            source: "UI_2.1/p2/images/Page2_05.png"
        }

        Row{
            anchors.top: parent.top
            anchors.left: parent.left

            Rectangle{
                width: rect1.width/2
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("序号")
                    font.pointSize: pointsize
                }
            }
            Rectangle{
                width: rect1.width/2
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("垃圾")
                    font.pointSize: pointsize
                }
            }

        }

        ListView{
            id:list
            width: rect1.width
            height: rect1.height-70

            anchors.top: parent.top
            anchors.topMargin: 70
            anchors.left: parent.left
            clip: true

			model: ListModel { id: trashList }

            delegate:Row{
                height:70
                width: 300
                //spacing: 50
                Rectangle{
                    width: parent.width/2
                    height: parent.height
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text:numbe
                        font.pointSize: 24
                    }
                }

                Rectangle{
                    width: parent.width/2
                    height: parent.height
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: name
                        font.pointSize: 24

                    }
                }
            }
			Connections {
        		target: videoCapture

        		function onFind_trash(counter, class_name) {
					trashList.append({
						numbe: counter,
						name: class_name
					})
        		}
    		}
            ScrollBar.vertical: ScrollBar{}
        }
    }

    Button {
        id: rect2
        width: parent.width - rect1.width - rect4.width - myspacing * 2
        height: 350
        anchors.top: rect1.top
        anchors.left: rect1.right
        anchors.leftMargin: 6
        background: Image {
            source: "UI_2.1/p2/images/Page2_08.png"
        }
    Image {
            id:img_cv
            asynchronous: false
            cache: false
            //anchors.fill: parent
		x: 45
		y: 15
		height: 320
        	width: 480
            //source: "image://mycv"
		source: "image://videoFrameProvider/frame"
        }
Connections {
        target: videoCapture

        function onFrame_ready() {
            
            img_cv.source = "image://videoFrameProvider/frame?" + Date.now();
        }
    }
    }
    Button {
        id: rect3
        width: rect2.width
        height: rect1.height - rect2.height - 10
        anchors.top: rect2.bottom
        anchors.topMargin: 10
        anchors.left: rect2.left

        background: Image {
            source: "UI_2.1/p2/images/Page2_15.png"
        }
        Row{
            id:tag
            anchors.top: parent.top
            anchors.left: parent.left

            Rectangle{
                width: rect3.width/4
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("序号")
                    font.pointSize: pointsize
                }
            }
            Rectangle{
                width: rect3.width/4
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("类别")
                    font.pointSize: pointsize
                }
            }
            Rectangle{
                width: rect3.width/4
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("数量")
                    font.pointSize: pointsize
                }
            }
            Rectangle{
                width: rect3.width/4
                height: 70
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: qsTr("R/N")
                    font.pointSize: pointsize
                }
            }

        }

        Row{
            anchors.top: tag.bottom
            anchors.left: parent.left

            Column {
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("1")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("2")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("3")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("4")
                        font.pointSize: pointsize
                    }
                }


            }

            Column{
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("可回收")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("有害")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("厨余")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("其它")
                        font.pointSize: pointsize
                    }
                }

            }

            Column {
                Rectangle{

                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        id:num1
                        anchors.centerIn: parent
                        text: count1
                        font.pointSize: pointsize
                    }
                }
                Rectangle{

                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        id:num2
                        anchors.centerIn: parent
                        text: count2
                        font.pointSize: pointsize
                    }
                }
                Rectangle{

                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        id:num3
                        anchors.centerIn: parent
                        text: count3
                        font.pointSize: pointsize
                    }
                }
                Rectangle{

                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        id:num4
                        anchors.centerIn: parent
                        text: count4
                        font.pointSize: pointsize
                    }
                }
				Connections {
        			target: videoCapture
        			function onFind_trash(counter, class_name) {
						if(class_name == "recycle")
							num1.text++
						else if(class_name == "harmful")
							num2.text++
						else if(class_name == "kitchen")
							num3.text++
						else if(class_name == "others")
							num4.text++

        			}
    			}


            }

            Column {
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("ok")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("ok")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("ok")
                        font.pointSize: pointsize
                    }
                }
                Rectangle{
                    width: rect3.width/4
                    height: 70
                    color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("ok")
                        font.pointSize: pointsize
                    }
                }
            }
        }

    }
    Button {
        id: rect4
        width: 400
        height: 590
        anchors.top: rect1.top
        anchors.right: parent.right
        background: Image {
            source: "UI_2.1/p2/images/Page2_11.png"
        }

        Text {
            id: check
            text: "满溢检测"
            font.pointSize: 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

        }

        Column{
            spacing: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: check.bottom
            anchors.topMargin: 20

            Row {
                id:trash_check
                spacing: 20
                Rectangle{
                    id:trash_type1
                    width: rect4.width/4
                    height: 40
                    color: "white"
                    Text {
                        text: "1"
                        font.pointSize: 24
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash_type2
                    width: rect4.width/4
                    height: 40
                    color: "gray"
                    Text {
                        text: "可回收"
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash_type3
                    width: rect4.width/4
                    height: 40
                    color: trash1_color
                    Text {
                        text: trash1_text
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
            Row {
                id:trash1_check
                spacing: 20
                Rectangle{
                    id:trash1_type1
                    width: rect4.width/4
                    height: 40
                    color: "white"
                    Text {
                        text: "2"
                        font.pointSize: 24
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash1_type2
                    width: rect4.width/4
                    height: 40
                    color: "gray"
                    Text {
                        text: "有害"
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash1_type3
                    width: rect4.width/4
                    height: 40
                    color: trash2_color
                    Text {
                        text: trash2_text
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
            Row {
                id:trash2_check
                spacing: 20
                Rectangle{
                    id:trash2_type1
                    width: rect4.width/4
                    height: 40
                    color: "white"
                    Text {
                        text: "3"
                        font.pointSize: 24
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash2_type2
                    width: rect4.width/4
                    height: 40
                    color: "gray"
                    Text {
                        text: "厨余"
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash2_type3
                    width: rect4.width/4
                    height: 40
                    color: trash3_color
                    Text {
                        text: trash3_text
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
            Row {
                id:trash3_check
                spacing: 20
                Rectangle{
                    id:trash3_type1
                    width: rect4.width/4
                    height: 40
                    color: "white"
                    Text {
                        text: "4"
                        font.pointSize: 24
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash3_type2
                    width: rect4.width/4
                    height: 40
                    color: "gray"
                    Text {
                        text: "其它"
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    id:trash3_type3
                    width: rect4.width/4
                    height: 40
                    color: trash4_color
                    Text {
                        text: trash4_text
                        font.pointSize: 24
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
			Connections {
        		target: videoCapture

        		function onIs_full(one, two, three, four) {
					if(one == 1) {
						trash1_color = "red"
						trash1_text = "R"
					}
					else {
						trash1_color = "green"
						trash1_text = "N"
					}
					if(two == 1) {
						trash2_color = "red"
						trash2_text = "R"
					}
					else {
						trash2_color = "green"
						trash2_text = "N"
					}
					if(three == 1) {
						trash3_color = "red"
						trash3_text = "R"
					}
					else {
						trash3_color = "green"
						trash3_text = "N"
					}
					if(four == 1) {
						trash4_color = "red"
						trash4_text = "R"
					}
					else {
						trash4_color = "green"
						trash4_text = "N"
					}
        		}
    		}
        }



    }
    Row {
        id: buts_cv
        spacing: 20
        anchors.horizontalCenter: rect4.horizontalCenter
        anchors.top: but_reten1.bottom
        anchors.topMargin: 10
        y:630
        Button {
            id: but_cv
            width: cvbut_width
            height: cvbut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p2/images/Page2_01.png"
            }
            onClicked: {
				videoCapture.condense()
//                inactivityTimer.restart()
//                mycv2.changeflag_cv()

            }
        }
        Button {

            id: but_shot
            width: cvbut_width
            height: cvbut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p2/images/Page2_02.png"
            }
            property int flag: 0
            onClicked: {
				videoCapture.checkFull()
//               inactivityTimer.restart()
//               con.img_path("hhel")

            }
        }
        Button {
            id: but_main
            width: cvbut_width
            height: cvbut_heigth
            opacity: pressed ? 0.3 : 1
            background: Image {
                source: "UI_2.1/p2/images/Page2_03.png"
            }
            onClicked: {
                myloader.sourceComponent = page_main
            }
        }

    }
//    Row {
//        id: buts_reten
//        spacing: 20
//        anchors.horizontalCenter: rect4.horizontalCenter
//        anchors.bottom: but_cv.top
//        y:520
////        anchors.topMargin: 10

//        Button {
//            id: but_reten1
//            width: cvbut_width
//            height: cvbut_heigth
//            opacity: pressed ? 0.3 : 1
//            background: Image {
//                source: "UI_2.1/p0/images/Page0_11.png"
//            }
//            onClicked: {
//                myloader.sourceComponent = page_main
//            }
//        }
//        Button {
//            id: but_reten2
//            width: cvbut_width
//            height: cvbut_heigth
//            opacity: pressed ? 0.3 : 1
//            background: Image {
//                source: "UI_2.1/p0/images/Page0_09.png"
//            }
//            onClicked: {
//                myloader.sourceComponent = page_video
//            }
//        }
//        Button {
//            id: but_reten3
//            width: cvbut_width
//            height: cvbut_heigth
//            opacity: pressed ? 0.3 : 1
//            background: Image {
//                source: "UI_2.1/p0/images/Page0_16.png"
//            }
//            onClicked: {
//                // 在这里执行关机操作
//                 Qt.quit();
//            }
//        }
//    }
//                Timer {
//                    id: inactivityTimer
//                    interval: 10000 // 5秒后自动跳转
//                    running: true
//                    repeat: false
//                    onTriggered: {
//                        myloader.sourceComponent = page_video
////                        inactivityTimer.running=false
//                    }
//                }
//                onCountChanged: {
//                    // 数据值发生变化时重置计时器
//                    inactivityTimer.restart()
//                }

}
