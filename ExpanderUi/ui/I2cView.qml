import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


RowLayout {
    spacing: 5

    I2cConfigPanel {
        Layout.fillHeight: true
        Layout.preferredWidth: (parent.width - parent.spacing) / 3
        Layout.minimumWidth: 300
    }

    I2cLogPanel {
        Layout.fillHeight: true
        Layout.preferredWidth: (parent.width - parent.spacing) * 2 / 3
    }
}
