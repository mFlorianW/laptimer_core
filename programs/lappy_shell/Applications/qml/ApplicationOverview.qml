// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import Lappy.Shell.Applications

Rectangle {
    id: root
    color: palette.window

    GridView {
        id: applicationsOverview
        anchors.fill: parent
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        model: model
        cellWidth: 150
        cellHeight: 70

        highlight: Rectangle {
            color: palette.highlight
            radius: 5
        }

        delegate: ApplicationButton {
            appName: name
            iconSource: icon

            onClicked: {
                applicationsOverview.currentIndex = index;
            }
        }
    }
}
