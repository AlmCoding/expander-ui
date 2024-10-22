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

        I2cLogListPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - requestForm.visible * (requestForm.height + formMargin) - (buttonRow.height + parent.spacing)
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
                    id: clearButton
                    Layout.preferredWidth: 90
                    text: "Clear"
                    onClicked: function() {
                        rootStore.i2cStore.i2cLogModel.clearModel();
                    }
                }
                Button {
                    id: fileButton
                    Layout.preferredWidth: 90
                    Layout.rightMargin: parent.spacing
                    text: "&File"
                }
            }
        }

        I2cRequestFormPanel {
            id: requestForm
            Layout.fillWidth: true
            Layout.preferredHeight: 270
            Layout.topMargin: formMargin
            visible: rootStore.i2cStore.i2cRequestForm.visible
        }
    }
}
