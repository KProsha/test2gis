#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QFile>
#include <QSharedPointer>
#include <QTextStream>

#include "histogramstate.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    enum StateType{
        STATEREADY,
        STATEBUSY,
        STATEEND
    };

    explicit Parser(QObject *parent = nullptr);

public slots:
    void parseFile(const QString &fileName);
    void breakWork();

signals:
    void sigState(HistogramState state);
    void sigPercent(int value);

    void sigContinue();

private slots:
    void continueParse();

private:
    StateType _state;

    const static int _viewedWordCount = 15;
    const static int _blockWordCont = 20000;

    qint64 _fileSize;

    QHash<QString, int> _dictionary;
    QMap<QString, int> _viewedWord;

    QSharedPointer<QFile> _file;
    QSharedPointer<QTextStream> _stream;

};


#endif // PARSER_H
