// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import QtCore

ApplicationWindow {
    id: applicationWindow
    title: "Lappy"

    minimumWidth: 1024
    minimumHeight: 768

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            Action {
                text: qsTr("Open GPS file")
                shortcut: "Ctrl+o"
                icon.name: "document-open"
                onTriggered: fileDialog.open()
            }

            Action {
                id: actionGpsSource
                text: qsTr("Start GPS source")
                onTriggered: !g_MainWindowViewModel.gpsSourceActive ? g_MainWindowViewModel.startGpsSource() : g_MainWindowViewModel.stopGpsSource()
            }

            MenuSeparator {}

            Action {
                text: qsTr("Quit")
                icon.name: "application-exit"
            }
        }

        Menu {
            title: qsTr("Track")

            ActionGroup {
                id: trackChooseGroup
                exclusive: true
            }

            Action {
                text: qsTr("Oschersleben")
                checkable: true
                ActionGroup.group: trackChooseGroup
            }
            Action {
                text: qsTr("Assen")
                checkable: true
                ActionGroup.group: trackChooseGroup
            }
            Action {
                text: qsTr("Most")
                checkable: true
                ActionGroup.group: trackChooseGroup
            }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                icon.name: "help-about"
            }
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 0

            ToolButton {
                icon.name: "document-open"
                onClicked: fileDialog.open()
                Layout.alignment: Qt.AlignLeft

                ToolTip {
                    text: qsTr("Open GPS position file")
                }
            }

            ToolButton {
                id: toolButtonGpsSource
                onClicked: !g_MainWindowViewModel.gpsSourceActive ? g_MainWindowViewModel.startGpsSource() : g_MainWindowViewModel.stopGpsSource()
                Layout.alignment: Qt.AlignLeft
                ToolTip {
                    text: qsTr("Start GPS source")
                }
            }

            Label {
                id: activeLaptime
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                text: g_MainWindowViewModel.currentLaptime
            }

            Slider {
                Layout.alignment: Qt.AlignRight
                from: 1
                to: 300
                value: 10
                enabled: true
                ToolTip {
                    text: qsTr("Velocity GPS source")
                }
            }
        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical
        SplitView.maximumWidth: 500
        SplitView.minimumHeight: applicationWindow.height - lowerSplitView.minimumHeight

        ListView {
            id: lapView
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: 400
            boundsBehavior: ListView.StopAtBounds

            model: g_MainWindowViewModel.laptimeModel

            delegate: Text {
                width: lapView.width
                text: "Lap " + index + ": " + laptime
            }
        }

        SplitView {
            id: lowerSplitView
            SplitView.minimumHeight: 200

            ListView {
                id: gpsPositionsView
                height: 200
                implicitWidth: 400
                boundsBehavior: ListView.StopAtBounds

                header: Rectangle {
                    height: 40
                    anchors.left: parent.left
                    anchors.right: parent.right
                    color: "black"
                    //                    radius: 0.03 * root.width
                    RowLayout {
                        anchors.fill: parent

                        Text {
                            id: indexText
                            Layout.alignment: Qt.AlignHCenter
                            //                            paintedWidth: parent.width / 10
                            text: qsTr("Pos Number")
                            color: "white"
                        }

                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            //                            width: parent.width / 4.5
                            text: qsTr("Longitude")
                            color: "white"
                        }
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            //                            width: parent.width / 4.5
                            text: qsTr("Latitude")
                            color: "white"
                        }
                    }
                }
            }

            Map {
                id: map
                plugin: Plugin {
                    id: mapPlugin
                    preferred: ["osm"]
                }
                center: QtPositioning.coordinate(52.0270889, 11.2803483)
                zoomLevel: 16
                activeMapType: supportedMapTypes[1]

                MapCircle {
                    id: currentPostion
                    radius: 5.0
                    color: "red"
                    border.width: 1
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a GPS file"
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]

        onAccepted: {
            g_MainWindowViewModel.loadGpsFile(fileDialog.fileUrl);
        }
    }

    Connections {
        target: g_MainWindowViewModel
        function onCurrentPositionChanged() {
            currentPostion.center = g_MainWindowViewModel.currentPosition;
        }
    }

    Item {
        id: stateItem
        states: [
            State {
                name: "GpsSourceActive"
                when: g_MainWindowViewModel.gpsSourceActive === true
                PropertyChanges {
                    target: actionGpsSource
                    icon.name: "media-playback-stop"
                }
                PropertyChanges {
                    target: toolButtonGpsSource
                    icon.name: "media-playback-stop"
                }
            },
            State {
                name: "GpsSourceInactive"
                when: g_MainWindowViewModel.gpsSourceActive === false
                PropertyChanges {
                    target: actionGpsSource
                    icon.name: "media-playback-start"
                }
                PropertyChanges {
                    target: toolButtonGpsSource
                    icon.name: "media-playback-start"
                }
            }
        ]
    }
}
