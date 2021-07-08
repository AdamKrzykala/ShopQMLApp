#include "cart.h"
#include <QMessageBox>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

Cart::Cart(QObject *parent) : QObject(parent)
{
    this->manager = std::make_unique<QNetworkAccessManager>();
}

QVector<CartItem> Cart::items() const
{
    return mItems;
}

bool Cart::setItemAt(int index, const CartItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void Cart::appendItem(QString name, float weight, int price)
{
    auto isPresent = [name](CartItem item){
        if (item.name == name) return true;
        return false;
    };
    auto findingResult = std::find_if(std::begin(mItems), std::end(mItems), isPresent);

    if (findingResult == std::end(mItems)) {
        emit preItemAppended();

        CartItem newItem = {name, weight, price, 1};
        mItems.append(newItem);

        emit postItemAppended();
    }
    else {
        findingResult->amount += 1;
    }

    QMessageBox msgBox;
    msgBox.setText("Product has been added to cart.");
    msgBox.exec();
}


void Cart::editingFinished(QString name, QString textInput)
{
    // Change amount
    int newAmount = textInput.toInt();
    auto isPresent = [name](CartItem item){
        if (item.name == name) return true;
        return false;
    };

    auto findingResult = std::find_if(std::begin(mItems), std::end(mItems), isPresent);

    if (findingResult != std::end(mItems)) {
        findingResult->amount = newAmount;
    }

    // Calculate price
    int priceToSend = 0;
    for (CartItem item : this->mItems) {
        priceToSend += item.amount * item.price;
    }

    // Send request with price
    QString stringRequest = "http://127.0.0.1:5000/order_request";
    QString postData;

    QUrlQuery query;
    query.addQueryItem("price", QStringLiteral("%1").arg(priceToSend));

    postData = query.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkRequest request;
    QUrl url = QUrl(stringRequest + "?" + postData);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = nullptr;

    reply = this->manager->post(request, "");

    connect(reply, &QNetworkReply::finished, [=]() {

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject obtainedPrice = document.object();
            int result = obtainedPrice[QString("result")].toInt();
            qDebug() << "Price result is: " << result;
        }
        else // handle error
        {
          qDebug() << reply->errorString();
        }
    });


}
