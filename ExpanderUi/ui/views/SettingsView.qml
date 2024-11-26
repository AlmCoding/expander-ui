import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../panels"

Rectangle {
    anchors.fill: parent
    color: "lightgray"

    ColumnLayout {
        // anchors.fill: parent
        width: parent.width
        //anchors.topMargin: 10
        spacing: 10

        ConnectionPanel {
            Layout.preferredWidth: 400
            Layout.topMargin: 10
            // Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        DeviceInfoPanel {
            Layout.preferredWidth: 400
            // Layout.preferredHeight: 200
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
