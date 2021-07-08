#ifndef SHOP_H
#define SHOP_H

#include <QObject>
#include <QVector>
#include <QNetworkAccessManager>
#include <QUrl>

struct ShopItem
{
    QString name;
    float weight;
    int price;
};

class Shop : public QObject
{
    Q_OBJECT
public:
    explicit Shop(QObject *parent = nullptr);

    QVector<ShopItem> items() const;

    bool setItemAt(int index, const ShopItem &item);

private:
    std::unique_ptr<QNetworkAccessManager> manager;
    QVector<ShopItem> shopItems_;
};

#endif // SHOP_H
