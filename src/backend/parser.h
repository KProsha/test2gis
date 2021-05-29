#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QHash>
#include <QString>

#include "histogramstate.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

public slots:
    void parceFile(const QString &fileName);

signals:
    void sigState(HistogramState state);
    void sigPercent(int value);

private:
    QHash<QString, int> _dictionary;

};


#endif // PARSER_H
