import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Shop 1.0
import Cart 1.0

Frame {

    Text {
        property string textContent: "Products Available"
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

        model: ShopModel {
            list: shopList
        }

        delegate: RowLayout {
            width: parent.width
            spacing: 10

            Label {
                Layout.fillWidth: true
                text: "Name: "
            }

            Label {
                Layout.fillWidth: true
                text: model.name
            }

            Label {
                Layout.fillWidth: true
                text: "Weight[g]: "
            }

            Label {
                Layout.fillWidth: true
                text: model.weight
            }

            Label {
                Layout.fillWidth: true
                text: "Price[PLN]: "
            }

            Label {
                Layout.fillWidth: true
                text: model.price
            }

            Button {
                id: addButton
                text: "Add to cart"
                onClicked: cartList.appendItem(model.name, model.weight, model.price)
            }
        }
    }
}
