// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

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
                text: qsTr("Download Sessions")
                icon.name: "download"
                //shortcut: "Ctrl+q"
                onTriggered: g_MainWindowModel.startSessionDownload()
            }


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
            
            ToolButton{
                icon.name: "download"
                onClicked: g_MainWindowModel.startSessionDownload()

                ToolTip{
                    text: qsTr("Start Session Download");
                }
            }

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
            text: g_MainWindowModel.logMessage
        }
    }
}

