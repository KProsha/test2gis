#include "parser.h"

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTextCodec>

#include <QDebug>

Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::parceFile(const QString& fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int percent = 0;
    qint64 fileSize = file->size();

    QMap<QString, int> top15;

    QTextStream stream(file.data());
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);

    while(!stream.atEnd()){
        QString rawWord;
        stream >> rawWord;

        QStringList rawWordList;
        rawWordList = rawWord.split(QRegularExpression("[\\.\\,\\!\\@\\#\\*\\+\\-\\<\\>\\{\\}\\[\\]\\(\\)\\|\\'\\\"\\?\\/\\\\]"), Qt::SkipEmptyParts);

        foreach(QString word, rawWordList){
            // ----- dictionary -----

            int wordCount = _dictionary.value(word);
            ++wordCount;

            _dictionary.insert(word, wordCount);

            // ----- get 15 most frequent  -----
            QString keyToDelete;
            int minValue = wordCount;

            if(top15.count() < 15){
                top15.insert(word, wordCount);
            } else {
                for(auto it = top15.begin(); it != top15.end(); ++it){
                    if(it.value() < minValue){
                        keyToDelete = it.key();
                        minValue = it.value();
                    }
                }

                if(!keyToDelete.isEmpty()){
                    top15.remove(keyToDelete);
                    top15.insert(word, wordCount);
                }
            }

            // ----- progress -----
            int newPercent = static_cast<int>((stream.pos() * 100) / fileSize);
            if(newPercent > percent){
                percent = newPercent;

                emit sigPercent(newPercent);
                emit sigState(top15);
            }
        }
    }

    emit sigPercent(100);
    emit sigState(top15);

    file->close();
}
