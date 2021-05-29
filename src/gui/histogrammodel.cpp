#include "histogrammodel.h"

#include <QPair>
#include <QDebug>

HistogramModel::HistogramModel(QObject* parent): QAbstractListModel(parent)
{
    _percent = 0;
    _maxValue = 0;
}

int HistogramModel::count() const
{
    return _data.count();
}

int HistogramModel::rowCount(const QModelIndex& parent) const
{
    return count();
}

QVariant HistogramModel::data(const QModelIndex& index, int role) const
{
    if((index.row() < 0) || (index.row() >= _data.size())) return QVariant();

    if(role == ValueRole) {
        return _data[index.row()].second;
    }

    return QVariant();
}

QVariant HistogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((section < 0) || (section >= _data.size())) return QVariant("");
    return _data[section].first;
}

QHash<int, QByteArray> HistogramModel::roleNames() const
{
    return {
      {ValueRole,"valueRole"}
    };
}

int HistogramModel::maxValue() const
{
    return _maxValue;
}

QString HistogramModel::fileName() const
{
    return _fileName;
}

void HistogramModel::setFileName(const QString& fileName)
{
    _fileName = fileName;
    emit sigFileNameChanged();
}

int HistogramModel::percent() const
{
    return _percent;
}

void HistogramModel::setPercent(int percent)
{
    _percent = percent;
    emit sigPercentChanged();
}

void HistogramModel::setData(HistogramState state)
{
    beginResetModel();
    _data.clear();
    _maxValue = 0;

    for(auto it = state.begin(); it != state.end(); ++it){
        _data.append(QPair<QString, int>(it.key(), it.value()));
        _maxValue = qMax(_maxValue, it.value());
    }

    endResetModel();
}

