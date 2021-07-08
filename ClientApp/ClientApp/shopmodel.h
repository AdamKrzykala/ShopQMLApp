#ifndef SHOPMODEL_H
#define SHOPMODEL_H

#include <QAbstractListModel>
#include <shop.h>
#include <memory>


class ShopModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Shop *list READ list WRITE setList)

public:
    explicit ShopModel(QObject *parent = nullptr);

    enum {
        NameRole,
        WeightRole,
        PriceRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Shop* list() const;
    void setList(Shop *list);

private:
    Shop *shopList;
};

#endif // SHOPMODEL_H
