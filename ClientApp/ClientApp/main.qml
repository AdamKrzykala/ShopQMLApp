import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Shop 1.0
import Cart 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Shop"

    header:ToolBar{
        RowLayout {
            anchors.fill: parent
            spacing: 3
            Image {
                horizontalAlignment: Image.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
                width: 100
                height: 100
                id: list_icon
                source: "icons/list_icon.png"

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.push(shop)
                    }
                 }
            }

            Image {
                horizontalAlignment: Image.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
                width: 100
                height: 100
                id: shop_icon
                source: "icons/shop_icon.png"

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.push(cart)
                    }
                 }
            }

            Image {
                horizontalAlignment: Image.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
                width: 100
                height: 100
                id: settings_icon
                source: "icons/setting_icon.png"

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.push(setting)
                    }
                 }
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent

    }

    Component {
        id: shop
        Shop {
            anchors.centerIn: parent
        }
    }

    Component {
        id: cart
        Cart {
            anchors.centerIn: parent
        }
    }

    Component {
        id: setting

        Settings {
            anchors.centerIn: parent
        }
    }
}

