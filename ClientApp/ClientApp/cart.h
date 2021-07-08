#ifndef CART_H
#define CART_H

#include <QObject>
#include <QVector>
#include <QNetworkAccessManager>
#include <QDebug>

struct CartItem
{
    QString name;
    float weight;
    int price;
    uint amount;
};

class Cart : public QObject
{
    Q_OBJECT
public:
    explicit Cart(QObject *parent = nullptr);

    QVector<CartItem> items() const;

    bool setItemAt(int index, const CartItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    // void preItemRemoved(int index);
    // void postItemRemoved();

public slots:
    void appendItem(QString, float, int);
    void editingFinished(QString, QString);
    // void removeCompletedItems();

private:
    std::unique_ptr<QNetworkAccessManager> manager;
    QVector<CartItem> mItems;
};

#endif // CART_H
