import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Item {
    width: requestList.width  // TODO: Is this ok?
    height: 60

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 5

        RowLayout {
            id: firstRow
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 2

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 20
                color: "red"
                // Text { text: req_type}
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

        Rectangle {
            id: secondRow
            //Layout.fillWidth: true
            Layout.preferredWidth: parent.width - 20
            Layout.preferredHeight: parent.height / 2
            color: "green"
        }

        // RowLayout {
        //     id: secondRow
        //     Layout.fillWidth: true
        //     Layout.preferredHeight: parent.height / 2

        //     // Text {
        //     //     Layout.preferredWidth: 100 // parent.width - playImage.width
        //     //     text: '<b>Data:</b> ' + write_data
        //     // }

        //     Rectangle {
        //         Layout.fillHeight: true
        //         Layout.preferredWidth: 100
        //         color: "green"
        //     }

        //     Image {
        //         id: playImage
        //         Layout.preferredHeight: 20
        //         fillMode: Image.PreserveAspectFit
        //         source: "/ExpanderUi/ui/resources/images/play_button.png"
        //     }
        // }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: requestList.currentIndex = index
    }
}
