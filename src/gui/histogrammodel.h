#ifndef HISTOGRAMMODEL_H
#define HISTOGRAMMODEL_H

#include <QAbstractListModel>

class HistogramModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY sigCountChanged)
    Q_PROPERTY(int maxValue READ maxValue NOTIFY sigMaxValueChanged)

public:
    const int ValueRole = Qt::UserRole;

    HistogramModel(QObject *parent = nullptr);
    HistogramModel(const HistogramModel& other){
    }

    int count() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int maxValue() const;

signals:
    void sigCountChanged();
    void sigMaxValueChanged();


private:


};

#endif // HISTOGRAMMODEL_H
