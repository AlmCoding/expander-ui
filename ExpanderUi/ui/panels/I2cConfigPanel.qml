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
            id: configPanel
            Layout.fillWidth: true
            Layout.preferredHeight: 320
            // Layout.leftMargin: 10
        }

        Rectangle {
            id: spacingRect
            Layout.fillWidth: true
            Layout.preferredHeight: 5
            color: "#00BCD4"
        }

        I2cRequestListPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - configPanel.height - spacingRect.height
            // Layout.leftMargin: 10
        }
    }
}
