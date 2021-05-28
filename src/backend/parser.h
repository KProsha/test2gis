#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QPair>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

public slots:
    void parceFile(const QString &parameter);

signals:
    void sigState(QList<QPair<QString, int> > state);
    void sigPercent(int value);

private:
    QHash<QString, int> _dictionary;

};



#endif // PARSER_H
