#include "CartModel.h"

CartModel::CartModel(CartService &cart, QObject* parent) : cart(cart) {}

int CartModel::rowCount(const QModelIndex &parent) const
{
    return this->cart.getSize();
}

int CartModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant CartModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    TrenchCoat tc = this->cart.getOnPos(row);

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
            case 0:
                return QString::fromStdString(tc.getSize());
            case 1:
                return QString::fromStdString(tc.getColor());
            case 2:
                return QString::fromStdString(tc.getPhoto());
            case 3:
                return QString::number(tc.getPrice());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant CartModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch (section)
            {
                case 0:
                    return QString("Size");
                case 1:
                    return QString("Color");
                case 2:
                    return QString("Photo");
                case 3:
                    return QString("Price");
                default:
                    break;
            }
        }
    }
    return QVariant();
}

void CartModel::addTC(const TrenchCoat &tc)
{
    int n = this->cart.getSize();
    this->beginInsertRows(QModelIndex(), n, n);
    this->cart.addToEnd(tc);;
    this->endInsertRows();
}





