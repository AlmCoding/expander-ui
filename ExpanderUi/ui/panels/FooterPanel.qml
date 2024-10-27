import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    id: footer
    color: "#00BCD4"

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 10

        Row {
            id: leftRow
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.leftMargin: parent.spacing
            Layout.rightMargin: parent.spacing
            spacing: 10

            Label {
                id: fileName
                anchors.verticalCenter: parent.verticalCenter
                //font.bold: true
                text: rootStore.i2cStore.i2cRequestModel.filePath
            }

            Image {
                id: fileImage
                height: parent.height - leftRow.spacing
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: "/ExpanderUi/ui/resources/images/file_52.png"
                visible: rootStore.i2cStore.i2cRequestModel.filePath !== ""
            }
        }

        Row {
            id: centertRow
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.rightMargin: parent.spacing
            spacing: 10

            Label {
                id: statusMessage
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
                text: rootStore.interfaceExpander.statusMessage
            }

            // Image {
            //     id: statusImage
            //     height: parent.height - centertRow.spacing
            //     fillMode: Image.PreserveAspectFit
            //     anchors.verticalCenter: parent.verticalCenter
            //     source: rootStore.interfaceExpander.isConnected === false ? "/ExpanderUi/ui/resources/images/disconnected_50.png" : "/ExpanderUi/ui/resources/images/connected_50.png"
            // }
        }

        Row {
            id: rightRow
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.rightMargin: parent.spacing
            spacing: 10

            Label {
                id: connectionStatus
                anchors.verticalCenter: parent.verticalCenter
                //font.bold: true
                text: rootStore.interfaceExpander.isConnected === false ? "Disconnected" : "Connected"
            }

            Image {
                id: connectionStatusImage
                height: parent.height - rightRow.spacing
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: rootStore.interfaceExpander.isConnected === false ? "/ExpanderUi/ui/resources/images/disconnected_50.png" : "/ExpanderUi/ui/resources/images/connected_50.png"
            }
        }
    }
}
