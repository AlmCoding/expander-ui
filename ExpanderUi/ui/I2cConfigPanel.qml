import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    id: root
    color: "white"

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        I2cConfigInterfacePanel {
            Layout.fillWidth: true
            Layout.preferredHeight: (root.height - parent.spacing) / 4
            Layout.minimumHeight: 300
            Layout.leftMargin: 10
        }

        I2cConfigRequestPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: (root.height - parent.spacing) * 3 / 4
            // Layout.leftMargin: 10
        }
    }
}
