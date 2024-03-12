// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: applicationWindow
    title: "Lappy Laptimer"

    minimumWidth: 800
    minimumHeight: 600

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

        Menu{
            title: qsTr("Edit")

            Action {
                text: qsTr("Preferences")
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            Label {
                id: statusFooterLabel
                text: "Test Text"
            }
        }
    }
}
