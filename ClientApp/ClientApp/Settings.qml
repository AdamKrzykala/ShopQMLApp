import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


Frame {

    Text {
        id: titleText
        property string textContent: "Settings"
        font.pointSize: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#363636"
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideMiddle
        width: parent.width
        wrapMode: Text.Wrap
        text: textContent
    }

    RowLayout {
        width: parent.width * 0.4
        implicitWidth: 250
        clip:true
        anchors.centerIn: parent

        Label {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            text: "Server ip: "
        }

        TextField {
            Layout.alignment: Qt.AlignHCenter
            text: "127.0.0.1"
        }
    }
}
