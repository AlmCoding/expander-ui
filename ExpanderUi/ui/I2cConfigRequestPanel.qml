import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


ColumnLayout {
    id: root
    spacing: 5

    Rectangle {
        id: scrollRectangle
        Layout.fillWidth: true
        Layout.preferredHeight: parent.height - parent.spacing - newButton.height
        color: "lightgray"

        // Component {
        //     id: requestDelegate

        //     Item {
        //         width: requestList.width
        //         height: 40
        //         // color: "white"

        //         ColumnLayout {
        //             anchors.fill: parent

        //             RowLayout {
        //                 id: firstRow
        //                 Layout.fillWidth: true

        //                 Rectangle {
        //                     color: "red"
        //                     Layout.preferredWidth: 30
        //                     Text { text: req_type}
        //                 }
        //                 Rectangle {
        //                     color: "green"
        //                     Text { text: '<b>Name:</b> ' + req_type }
        //                 }
        //             }

        //             RowLayout {
        //                 id: secondRow
        //                 Layout.fillWidth: true
        //                 Text { text: '<b>Number:</b> ' + slave_addr }
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
        Layout.preferredWidth: scrollRectangle.width - 4 * root.spacing
        Layout.alignment: Qt.AlignHCenter
        text: "New"
    }
}
