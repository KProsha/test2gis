#include "backend.h"

Backend::Backend(QObject *parent): QObject(parent)
{
    _histogramModel = new HistogramModel(this);

}

HistogramModel* Backend::histogramModel() const
{
    return _histogramModel;
}

