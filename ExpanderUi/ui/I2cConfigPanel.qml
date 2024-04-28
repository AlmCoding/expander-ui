import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    color: "white"

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        I2cConfigInterfacePanel {
            Layout.fillWidth: true
            Layout.preferredHeight: (parent.height - parent.spacing) / 4
            Layout.minimumHeight: 330
            Layout.leftMargin: 10
        }

        I2cConfigRequestPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: (parent.height - parent.spacing) * 3 / 4
            // Layout.leftMargin: 10
        }
    }
}
