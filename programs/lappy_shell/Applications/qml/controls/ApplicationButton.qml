// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick

Item {
    id: root
    implicitHeight: 70
    implicitWidth: 100

    property alias iconSource: applicationIcon.source
    property alias appName: applicationName.text

    signal clicked
    signal doubleClicked

    Rectangle {
        id: hoverColor
        anchors.fill: parent
        visible: hoverHandler.hovered
        color: palette.highlight
        radius: 5
        opacity: 0.5
    }

    Item {
        id: applicationIconContainer
        height: root.implicitHeight / 2
        width: root.implicitWidth

        Image {
            id: applicationIcon
            height: 40
            width: height
            // anchors.centerIn: parent
            anchors.top: applicationIconContainer.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: applicationNameContainer
        anchors.top: applicationIconContainer.bottom
        anchors.topMargin: 10
        height: 20
        width: root.implicitWidth

        Text {
            id: applicationName
            anchors.centerIn: parent
            anchors.left: parent.left
            anchors.right: parent.right
            width: applicationNameContainer.width
            elide: Text.ElideRight
        }
    }

    HoverHandler {
        id: hoverHandler
    }

    MouseArea {
        id: applicationButtonMouseArea
        anchors.fill: parent

        onClicked: root.clicked()
        onDoubleClicked: root.doubleClicked()
    }
}
