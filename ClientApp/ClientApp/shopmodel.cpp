#include "shopmodel.h"
#include "shop.h"
#include <QDebug>

ShopModel::ShopModel(QObject *parent)
    : QAbstractListModel(parent)
    , shopList(nullptr)
{

}

int ShopModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !shopList)
        return 0;

    return shopList->items().size();
}

QVariant ShopModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ShopItem item = shopList->items().at(index.row());

    switch (role) {
    case NameRole:
        return QVariant(item.name);

    case WeightRole:
        return QVariant(item.weight);

    case PriceRole:
        return QVariant(item.price);
    }

    return QVariant();
}

bool ShopModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!shopList)
        return false;

    ShopItem item = shopList->items().at(index.row());
    switch (role) {
    case NameRole:
        item.name = value.toString();
        break;
    case WeightRole:
        item.weight = value.toFloat();
        break;
    case PriceRole:
        item.price = value.toInt();
        break;
    }

    if (shopList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ShopModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ShopModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[static_cast<int>(NameRole)]  = "name";
    names[static_cast<int>(WeightRole)]  = "weight";
    names[static_cast<int>(PriceRole)]  = "price";
    return names;
}

Shop *ShopModel::list() const
{
    return shopList;
}

void ShopModel::setList(Shop *list)
{
    beginResetModel();
    if (shopList) {
        shopList->disconnect(this);
    }

    shopList = list;

    endResetModel();
}


