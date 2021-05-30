#include "backend.h"

#include <QFileInfo>

Backend::Backend(QObject *parent): QObject(parent)
{
    parserThread = new QThread(this);

    _histogramModel = new HistogramModel(this);

    _parser = new Parser;
    _parser->moveToThread(parserThread);

    connect(parserThread, &QThread::finished, _parser, &QObject::deleteLater);

    connect(this, &Backend::sigParseFile, _parser, &Parser::parseFile);
    connect(this, &Backend::sigParseFile, _histogramModel, &HistogramModel::setFileName);

    connect(_parser, &Parser::sigState, _histogramModel, &HistogramModel::setData);
    connect(_parser, &Parser::sigPercent, _histogramModel, &HistogramModel::setPercent);

    parserThread->start();
}

Backend::~Backend()
{
    parserThread->quit();
    parserThread->wait();
}

HistogramModel* Backend::histogramModel() const
{
    return _histogramModel;
}

void Backend::setFileName(const QString& fileName)
{
    QFileInfo fileInfo(fileName);
    if(!fileInfo.exists()){
        emit sigError(tr("Нет такого файла"));
        return;
    }
    emit sigParseFile(fileName);
}

