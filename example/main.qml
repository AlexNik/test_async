import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //    menuBar: MenuBar {
    //        Menu {
    //            title: qsTr("File")
    //            MenuItem {
    //                text: qsTr("Exit")
    //                onTriggered: Qt.quit();
    //            }
    //        }
    //    }

    //    Component.onCompleted: SCProxy.rect = Qt.rect(0, 0, 1920, 1080)





    //    GridLayout {
    //        anchors.fill: parent

    //        columns: 2

    //        Button {
    //            text: "async"

    //            onClicked: SCProxy.takeScreenshot()
    //        }

    //        ProgressBar {
    //            id: progressBar

    //            maximumValue: 100
    //            minimumValue: 0

    //            //value: SCProxy.progress

    //            //onValueChanged: console.log(value)
    //        }

    //        Text {
    //            text: "Progress :"
    //        }

    //        Text {
    //            text: SCProxy.progress
    //        }

    //        Text {
    //            text: "File name"
    //        }

    //        Text {
    //            text: SCProxy.name
    //        }

    //        Text {
    //            text: "react size"
    //        }

    //        Text {
    //            text: SCProxy.rect.toString()
    //        }

    //        Button {
    //            text: "terminate"

    //            onClicked: SCProxy.work = false
    //        }

    //        Rectangle {
    //            id: rectangle
    //            width: 30
    //            height: 30

    //            color: "red"

    //            RotationAnimator {
    //                id: animator
    //                target: rectangle;
    //                from: 0;
    //                to: 360;
    //                duration: 1000
    //                //running: true

    //                loops: Animation.Infinite;

    //            }

    //            Connections {
    //                target: SCProxy

    //                onSaveBegin: animator.running = true
    //                onSaveEnd: animator.running = false

    //                onProgressChanged: {
    //                    progressBar.value = progress

    //                    SCProxy.rect = Qt.rect(0, 0, 1920 * (progress / 100), 1080 * (progress / 100))
    //                }
    //            }
    //        }
    //    }

    FileDialog {
        id: fileDialog
    }

    FileDialog {
        id: folderDialog

        selectFolder: true
    }

    Column {
        Column {
            Button {
                text: "Select file"

                onClicked: fileDialog.open()
            }

            Text {
                text: fileDialog.fileUrl
            }
        }

        Column {
            Button {
                text: "Select folder"

                onClicked: folderDialog.open()
            }

            Text {
                text: folderDialog.fileUrl
            }
        }

        Row {
            Button {
                text: "COPY!"

                onClicked: Proxy.copy(fileDialog.fileUrl, folderDialog.fileUrl)
            }
            Button {
                text: "Stop"
                onClicked: Proxy.stop = true
            }
        }

        ProgressBar {
            maximumValue: 100
            minimumValue: 0

            value: Proxy.progress
        }
    }


}
