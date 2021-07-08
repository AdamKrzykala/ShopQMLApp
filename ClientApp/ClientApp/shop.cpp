#include "shop.h"
#include <QDebug>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Shop::Shop(QObject *parent) : QObject(parent)
{
    this->manager = std::make_unique<QNetworkAccessManager>();
    QNetworkRequest request;
    QNetworkReply *reply = nullptr;
    QUrl url = QUrl("http://127.0.0.1:5000/getProducts");
    request.setUrl(url);

    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject obtainedProducts = document.object();
            QJsonArray products = obtainedProducts[QString("products")].toArray();
            for (auto product : products) {
                QJsonObject productObject = product.toObject();
                QString name = productObject["name"].toString();
                float weight = static_cast<float>(productObject["weight"].toDouble());
                int price = productObject["price"].toInt();
                shopItems_.append({name, weight, price});
            }
        }
        else // handle error
        {
          qDebug() << reply->errorString();
        }
    });
}

QVector<ShopItem> Shop::items() const
{
    return shopItems_;
}

bool Shop::setItemAt(int index, const ShopItem &item)
{
    if (index < 0 || index>= shopItems_.size())
        return false;

    shopItems_[index] = item;
    return true;
}
