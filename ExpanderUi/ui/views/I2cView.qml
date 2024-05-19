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
        Layout.preferredWidth: (parent.width - parent.spacing) / 3
        Layout.minimumWidth: 320
    }

    I2cLogPanel {
        Layout.fillHeight: true
        Layout.preferredWidth: parent.width - configPanel.width
        // Layout.preferredWidth: (parent.width - parent.spacing) * 2 / 3
    }
}
