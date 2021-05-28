#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSharedPointer>
#include <QThread>

#include "../gui/histogrammodel.h"
#include "parser.h"


class Backend: public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    HistogramModel* histogramModel() const;

    Q_INVOKABLE void setFileName(const QString& fileName);

signals:
    void sigParseFile(QString filename);

private:
    HistogramModel* _histogramModel;
    Parser* _parser;

    QThread* parserThread;
};

#endif // BACKEND_H
