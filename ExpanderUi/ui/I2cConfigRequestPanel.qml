import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


ColumnLayout {
    id: root
    spacing: 0

    Rectangle {
        id: scrollRectangle
        Layout.fillWidth: true
        Layout.preferredHeight: parent.height - newButton.height
        color: "lightgray"

        // Component {
        //     id: requestDelegate

        //     Item {
        //         width: requestList.width
        //         height: 60

        //         ColumnLayout {
        //             anchors.fill: parent
        //             anchors.leftMargin: 5

        //             RowLayout {
        //                 id: firstRow
        //                 Layout.fillWidth: true
        //                 Layout.preferredHeight: parent.height / 2

        //                 Rectangle {
        //                     color: "red"
        //                     Layout.preferredWidth: 20
        //                     Text { text: req_type}
        //                 }
        //                 Rectangle {
        //                     color: "green"
        //                     Layout.preferredWidth: 60
        //                     Text { text: "<b>Slave:</b> " + slave_addr }
        //                 }
        //                 Rectangle {
        //                     color: "red"
        //                     Layout.preferredWidth: 60
        //                     Text { text: "<b>Addr:</b> " + mem_addr }
        //                 }
        //                 Rectangle {
        //                     color: "blue"
        //                     Layout.preferredWidth: 60
        //                     Text { text: "<b>Size:</b> " + data_size }
        //                 }
        //             }

        //             RowLayout {
        //                 id: secondRow
        //                 Layout.fillWidth: true
        //                 Layout.preferredHeight: parent.height / 2

        //                 // Text {
        //                 //     Layout.preferredWidth: 100 // parent.width - playImage.width
        //                 //     text: '<b>Data:</b> ' + write_data
        //                 // }

        //                 Rectangle {
        //                     Layout.fillHeight: true
        //                     Layout.preferredWidth: 100
        //                     color: "green"
        //                 }

        //                 Image {
        //                     id: playImage
        //                     Layout.preferredHeight: 20
        //                     fillMode: Image.PreserveAspectFit
        //                     source: "/ExpanderUi/ui/resources/images/play_button.png"
        //                 }
        //             }
        //         }

        //         MouseArea {
        //             anchors.fill: parent
        //             onClicked: requestList.currentIndex = index
        //         }
        //     }
        // }

        ScrollView {
            anchors.fill: parent
            clip: true

            ListView {
                id: requestList
                anchors.fill: parent
                model: RequestModel {}
                delegate: I2cRequestListComponent {}
                highlight: Rectangle { color: "lightblue"; radius: 5 }
                focus: true
            }
        }
    }

    Button {
        id: newButton
        Layout.preferredWidth: scrollRectangle.width - 20
        Layout.alignment: Qt.AlignHCenter
        text: "New"
    }
}
