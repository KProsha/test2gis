#ifndef HISTOGRAMMODEL_H
#define HISTOGRAMMODEL_H

#include <QAbstractListModel>

#include "../backend/histogramstate.h"

class HistogramModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY sigCountChanged)
    Q_PROPERTY(int maxValue READ maxValue NOTIFY sigMaxValueChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY sigFileNameChanged)
    Q_PROPERTY(int percent READ percent NOTIFY sigPercentChanged)

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

    QString fileName() const;
    int percent() const;

public slots:
    void setFileName(const QString& fileName);
    void setPercent(int percent);
    void setData(HistogramState state);

signals:
    void sigCountChanged();
    void sigMaxValueChanged();
    void sigFileNameChanged();
    void sigPercentChanged();

private:
    QString _fileName;
    int _percent;
    int _maxValue;

    QList<QPair<QString, int> > _data;

};

#endif // HISTOGRAMMODEL_H
