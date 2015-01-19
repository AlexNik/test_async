import QtQuick 2.2
import QtQuick.Controls 1.1

import ScreenShotLib 1.0

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

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Button {

        width: 50
        height: 50

        text: "ASYNC"

        onClicked: {
            screenShotProxy.takeScreenshot()

//            qmlThread.start()
//            qmlThread.myId()
        }

//        QMLThread {
//            id: qmlThread
//        }
    }

    Rectangle {
        id: rect
        width: 100
        height: 100

        anchors.top: parent.top
        anchors.topMargin: height
        anchors.horizontalCenter: parent.horizontalCenter

        color: "red"

        RotationAnimator {
            id: animator
            target: rect;
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

    ProgressBar {
        id: progressBar

        maximumValue: 100
        minimumValue: 0

        anchors.centerIn: parent

        value: 50

//        onValueChanged: {
//            screenShotProxy.setRect(0,0,1920/(value+1), 1080/(value+1))
//        }

        Connections {
            target: screenShotProxy

            onProgress: progressBar.value = i
        }
    }

    ScreenShotProxy {
        id: screenShotProxy

        Component.onCompleted: setRect(0,0,1920,1080)
    }
}
