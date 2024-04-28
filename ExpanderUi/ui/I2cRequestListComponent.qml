import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Item {
    width: requestList.width  // TODO: Is this ok?
    height: 50

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 5

        RowLayout {
            id: firstRow
            Layout.fillWidth: true

            Rectangle {
                color: "red"
                Layout.preferredWidth: 20
                Text { text: req_type}
            }
            Rectangle {
                color: "green"
                Layout.preferredWidth: 60
                Text { text: "<b>Slave:</b> " + slave_addr }
            }
            Rectangle {
                color: "red"
                Layout.preferredWidth: 60
                Text { text: "<b>Addr:</b> " + mem_addr }
            }
            Rectangle {
                color: "blue"
                Layout.preferredWidth: 60
                Text { text: "<b>Size:</b> " + data_size }
            }
        }

        RowLayout {
            id: secondRow
            Layout.fillWidth: true
            Text { text: '<b>Data:</b> ' + write_data }

            // Image {
            //     Layout.preferredHeight: 10
            //     fillMode: Image.PreserveAspectFit
            //     source: "ExpanderUi/ui/resources/images/play_button.png"
            // }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: requestList.currentIndex = index
    }
}
