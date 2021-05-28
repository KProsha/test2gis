#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>

#include "../gui/histogrammodel.h"

class Backend: public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    HistogramModel* histogramModel() const;

private:
    HistogramModel* _histogramModel;

};

#endif // BACKEND_H
