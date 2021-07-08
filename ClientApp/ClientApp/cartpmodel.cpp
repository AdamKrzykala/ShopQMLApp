#include "cartmodel.h"

#include "cart.h"

CartModel::CartModel(QObject *parent)
    : QAbstractListModel(parent)
    , cartList(nullptr)
{
}

int CartModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !cartList)
        return 0;

    return cartList->items().size();
}

QVariant CartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const CartItem item = cartList->items().at(index.row());

    switch (role) {
    case NameRole:
        return QVariant(item.name);

    case WeightRole:
        return QVariant(item.weight);

    case PriceRole:
        return QVariant(item.price);

    case AmountRole:
        return QVariant(item.amount);
    }

    return QVariant();
}

bool CartModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!cartList)
        return false;

    CartItem item = cartList->items().at(index.row());
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
    case AmountRole:
        item.amount = value.toUInt();
    }

    if (cartList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CartModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> CartModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[static_cast<int>(NameRole)]  = "name";
    names[static_cast<int>(WeightRole)]  = "weight";
    names[static_cast<int>(PriceRole)]  = "price";
    names[static_cast<int>(AmountRole)] = "amount";
    return names;
}

Cart *CartModel::list() const
{
    return cartList;
}

void CartModel::setList(Cart *list)
{
    beginResetModel();

    if (cartList)
        cartList->disconnect(this);

    cartList = list;

    if (cartList) {
        connect(cartList, &Cart::preItemAppended, this, [=]() {
            const int index = cartList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(cartList, &Cart::postItemAppended, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}

