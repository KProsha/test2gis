#include "histogrammodel.h"

HistogramModel::HistogramModel(QObject* parent): QAbstractListModel(parent)
{


}

int HistogramModel::count() const
{
    return 15;
}

int HistogramModel::rowCount(const QModelIndex& parent) const
{
    return count();
}

QVariant HistogramModel::data(const QModelIndex& index, int role) const
{
    if(role == ValueRole) return index.row() * 100;

    return QVariant();
}

QVariant HistogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return "section " + QString::number(section);
}

QHash<int, QByteArray> HistogramModel::roleNames() const
{
    return {
      {ValueRole,"valueRole"}
    };
}

int HistogramModel::maxValue() const
{
    return 15 * 100;
}

