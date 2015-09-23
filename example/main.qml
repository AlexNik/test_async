import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Async example")

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
            id: buttonsRow

            Button {
                text: "COPY ASYNC!"

                onClicked: Proxy.copy(fileDialog.fileUrl, folderDialog.fileUrl)
            }
            Button {
                text: "Stop"
                onClicked: Proxy.stop = true
            }

            Button {
                text: "COPY SYNC!"

                onClicked: CopyClass.copy(fileDialog.fileUrl, folderDialog.fileUrl)
            }
        }

        ProgressBar {
            width: buttonsRow.width
            maximumValue: 100
            minimumValue: 0

            value: Proxy.progress

            Text {
                anchors.centerIn: parent
                text: Proxy.progress.toFixed(2) + " %"
            }
        }
    }


}
