import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../panels"

RowLayout {
    spacing: 5

    I2cConfigPanel {
        id: configPanel
        Layout.fillHeight: true
        Layout.preferredWidth:  Qt.platform.os === "windows" ? 325 : 340
    }

    I2cLogPanel {
        Layout.fillHeight: true
        Layout.preferredWidth: parent.width - configPanel.width
    }
}
