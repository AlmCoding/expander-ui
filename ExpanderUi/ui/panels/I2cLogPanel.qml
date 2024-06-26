import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    color: "#00BCD4"
    property int formMargin: 5

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - requestForm.visible * (requestForm.height + formMargin) - (buttonRow.height + parent.spacing)
            color: "light yellow"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: buttonRow.height
            Layout.alignment: Qt.AlignBottom
            color: "white"

            RowLayout {
                id: buttonRow
                anchors.right: parent.right
                spacing: 10

                Button {
                    id: saveButton
                    Layout.preferredWidth: 90
                    text: "Clear"
                }
                Button {
                    id: newButton
                    Layout.preferredWidth: 90
                    Layout.rightMargin: parent.spacing
                    text: "Save"
                }
            }
        }

        I2cRequestFormPanel {
            id: requestForm
            Layout.fillWidth: true
            Layout.preferredHeight: 270
            Layout.topMargin: formMargin
            // Layout.leftMargin: 10
            // Layout.rightMargin: 20
            // Layout.alignment: Qt.AlignBottom
            // Layout.preferredWidth: 600
            visible: rootStore.i2cRequestForm.visible
        }
    }
}
