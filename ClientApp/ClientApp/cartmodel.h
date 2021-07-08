#ifndef CARTMODEL_H
#define CARTMODEL_H

#include <QAbstractListModel>
#include <cart.h>

class CartModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Cart *list READ list WRITE setList)

public:
    explicit CartModel(QObject *parent = nullptr);

    enum {
        NameRole,
        WeightRole,
        PriceRole,
        AmountRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Cart *list() const;
    void setList(Cart *list);

private:
    Cart *cartList;
};

#endif // TODOMODEL_H
