#pragma once
#include <QAbstractTableModel>
#include "../Service/CartService.h"

class CartModel: public QAbstractTableModel
{
private:
    CartService& cart;

public:
    CartModel(CartService& cart, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addTC(const TrenchCoat& tc);
};