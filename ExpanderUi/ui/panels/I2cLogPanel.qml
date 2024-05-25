import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    color: "lightgray"

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - requestForm.visible * (requestForm.height + parent.spacing) - (buttonRow.height + parent.spacing)
            color: "light yellow"
        }

        I2cRequestFormPanel {
            id: requestForm
            Layout.fillWidth: true
            Layout.preferredHeight: 350
            // Layout.leftMargin: 10
            // Layout.rightMargin: 20
            // Layout.alignment: Qt.AlignBottom
            // Layout.preferredWidth: 600
            visible: rootStore.i2cRequestForm.visible
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
    }
}
