import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    id: footer
    color: constants.footerColor

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.leftMargin: parent.spacing
            Layout.rightMargin: parent.spacing
            implicitWidth: leftRow.implicitWidth
            visible: rootStore.i2cStore.i2cRequestModel.filePath !== ""
            color: footer.color

            Row {
                id: leftRow
                anchors.fill: parent
                spacing: 10

                Label {
                    id: fileName
                    anchors.verticalCenter: parent.verticalCenter
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
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.leftMargin: parent.spacing
            Layout.rightMargin: parent.spacing
            implicitWidth: centertRow.implicitWidth
            visible: rootStore.interfaceExpander.statusMessage !== ""
            color: footer.color

            Row {
                id: centertRow
                anchors.fill: parent
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
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.leftMargin: parent.spacing
            Layout.rightMargin: parent.spacing
            implicitWidth: rightRow.implicitWidth
            color: footer.color

            Row {
                id: rightRow
                anchors.fill: parent
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
}
