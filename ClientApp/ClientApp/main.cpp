#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "shopmodel.h"
#include "shop.h"
#include "cartmodel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ShopModel>("Shop", 1.0, 0, "ShopModel");
    qmlRegisterType<CartModel>("Cart", 1.0, 0, "CartModel");

    qmlRegisterUncreatableType<Shop>("Shop", 1, 0, "ShopList",
        QStringLiteral("Shop should not be created in QML"));
    qmlRegisterUncreatableType<Shop>("Cart", 1, 0, "CartList",
        QStringLiteral("Shop should not be created in QML"));

    Shop shopList;
    Cart cartList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("shopList"), &shopList);
    engine.rootContext()->setContextProperty(QStringLiteral("cartList"), &cartList);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
