import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

//import ScreenShotLib 1.0
import ScreenshotLib 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

//    Text {
//        text: qsTr("Hello World")
//        anchors.centerIn: parent
//    }

//    Button {

//        width: 50
//        height: 50

//        text: "ASYNC"

//        onClicked: {
//            //screenShotProxy.takeScreenshot()
//            screenShot.onTakeScreenshot()

////            qmlThread.start()
////            qmlThread.myId()
//        }

////        QMLThread {
////            id: qmlThread
////        }
//    }



//    ScreenShotProxy {
//        id: screenShotProxy

//        Component.onCompleted: setRect(0,0,1920,1080)
//    }

//    Screenshot {
//        id : screenShot

//        onProgressChanged: console.log(progress)
//    }

    ScreenShotProxy {
        id: screenShotProxy

        rect: Qt.rect(0, 0, 1920, 1080)

        onRectChanged: console.log(rect)

        onProgressChanged: {
            progressBar.value = progress

            rect = Qt.rect(0, 0, 1920 * (progress / 100), 1080 * (progress / 100))
        }

        Component.onDestruction: stop()
    }




    GridLayout {
        anchors.fill: parent

        columns: 2

        Button {
            text: "async"

            onClicked: screenShotProxy.takeScreenshot()
        }

        ProgressBar {
            id: progressBar

            maximumValue: 100
            minimumValue: 0

            value: 0

            onValueChanged: console.log(value)
        }

        Text {
            text: "Progress :"
        }

        Text {
            text: screenShotProxy.progress
        }

        Text {
            text: "File name"
        }

        Text {
            text: screenShotProxy.name
        }

        Text {
            text: "react size"
        }

        Text {
            text: screenShotProxy.rect.toString()
        }

        Button {
            text: "terminate"

            onClicked: screenShotProxy.stop()
        }

        Rectangle {
            id: rectangle
            width: 30
            height: 30

            color: "red"

            RotationAnimator {
                id: animator
                target: rectangle;
                from: 0;
                to: 360;
                duration: 1000
                //running: true

                loops: Animation.Infinite;

            }

            Connections {
                target: screenShotProxy

                onSaveBegin: animator.running = true
                onSaveEnd: animator.running = false
            }
        }
    }



}
