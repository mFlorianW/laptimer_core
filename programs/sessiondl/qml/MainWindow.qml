import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: applicationWindow
    title: "Lappy Session Downloader"

    minimumWidth: 480
    minimumHeight: 320

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            Action {
                text: qsTr("Quit")
                icon.name: "application-exit"
                shortcut: "Ctrl+q"
                onTriggered: Qt.quit()
            }
        }
    }

    header: ToolBar {
        RowLayout{
            spacing: 0
            
            Label {
                wrapMode: Label.Wrap
                text: "Host:"
                font.pixelSize: 16
            }

            TextField {
                id: serverIpInput
                implicitWidth: 150
                text: g_MainWindowModel.hostAddress 
                Layout.leftMargin: 5

                onEditingFinished: {
                    g_MainWindowModel.hostAddress = serverIpInput.text 
                }
            }

            Label {
                wrapMode: Label.Wrap
                text: "Port:"
                font.pixelSize: 16
                Layout.leftMargin: 5
            }

            TextField {
                id: serverPortInput
                implicitWidth: 50
                text: g_MainWindowModel.hostPort 
                Layout.leftMargin: 5

                onEditingFinished: {
                    g_MainWindowModel.hostPort = serverPortInput.text
                }
            }
        }
    }

    ScrollView {
        id: view
        anchors.fill: parent

        TextArea {
            text: "sdfljsdfljsdflkjsdlfkj \n TextArea\n...\n...\n...\n...\n...\n...\n"
        }
    }
}

