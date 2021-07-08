import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Cart 1.0

Frame {

    Text {
        property string textContent: "Your products"
        font.pointSize: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#363636"
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideMiddle
        width: parent.width
        wrapMode: Text.Wrap
        text: textContent
    }

    ListView {
        implicitHeight: 250
        width: parent.width * 0.9
        implicitWidth: 250
        clip:true
        anchors.centerIn: parent

        model: CartModel {
            list: cartList
        }

        delegate: RowLayout {
            width: parent.width
            spacing: 6

            Text {
                Layout.fillWidth: true
                text: "Name: "
            }

            Text {
                Layout.fillWidth: true
                text: model.name
            }

            Text {
                Layout.fillWidth: true
                text: "Weight: "
            }

            Text {
                Layout.fillWidth: true
                text: model.weight
            }

            Text {
                Layout.fillWidth: true
                text: "Price: "
            }

            Text {
                Layout.fillWidth: true
                text: model.price
            }

            Text {
                Layout.fillWidth: true
                text: "Amount: "
            }


            TextField {
                id: amountField
                Layout.fillWidth: true
                horizontalAlignment: TextInput.AlignHCenter
                text: model.amount
                onEditingFinished: cartList.editingFinished(model.name, amountField.text)
            }
        }
    }

    RowLayout {
        anchors.bottom: parent.bottom
        width: parent.width * 0.5
        implicitWidth: 250
        clip:true
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            font.pointSize: 12
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Total price is:")
        }

        TextField {
            id: totalPrice
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            font.pointSize: 14
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("PLN")
        }
    }
}
