import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

Rectangle {
    color: "lightgray"

    ScrollView {
        anchors.fill: parent
        clip: true

        ListView {
            id: logList
            anchors.fill: parent
            model: rootStore.i2cStore.i2cLogModel // listModel
            delegate: I2cLogListComponent {}
            highlight: Rectangle { color: constants.primaryColor; radius: 0 }
            highlightMoveDuration: constants.listViewHighlightMoveDuration
            focus: true
            currentIndex: rootStore.i2cStore.i2cLogModel.selectedLogIdx
        }
    }
}
