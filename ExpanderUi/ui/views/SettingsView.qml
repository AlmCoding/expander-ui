import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../panels"


Rectangle {
    anchors.fill: parent
    color: "lightgray"

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 10

        ConnectionPanel {
             Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        }
    }
}
