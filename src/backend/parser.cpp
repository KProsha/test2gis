#include "parser.h"

#include <QRegularExpression>
#include <QTextCodec>
#include <QSharedPointer>

#include <QDebug>

Parser::Parser(QObject *parent) : QObject(parent)
{
    _state = STATEREADY;

    connect(this, &Parser::sigContinue, this, &Parser::continueParse, Qt::QueuedConnection);
}

void Parser::parseFile(const QString& fileName)
{
    if(_state != STATEREADY) return;

    _dictionary.clear();
    _viewedWord.clear();

    _state = STATEBUSY;

    _file = QSharedPointer<QFile>(new QFile(fileName));

    if (!_file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    _fileSize = _file->size();

    _stream = QSharedPointer<QTextStream>(new QTextStream(_file.data()));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    _stream->setCodec(codec);

    emit sigContinue();
}

void Parser::breakWork()
{
    _state = STATEEND;
}

void Parser::continueParse()
{
    if(_state != STATEBUSY){

        _state = STATEREADY;
        return;
    }

    int wordReaded = 0;

    while(!_stream->atEnd()){
        QString rawWord;
        *_stream >> rawWord;

        QStringList rawWordList;
        rawWordList = rawWord.split(QRegularExpression("[\\.\\,\\!\\@\\#\\*\\+\\-\\<\\>\\{\\}\\[\\]\\(\\)\\|\\'\\\"\\?\\/\\\\]"), Qt::SkipEmptyParts);

        foreach(QString word, rawWordList){
            word = word.toLower();
            // ----- dictionary -----

            int wordCount = _dictionary.value(word);
            ++wordCount;

            _dictionary.insert(word, wordCount);

            // ----- get 15 most frequent  -----
            ++wordReaded;

            if(_viewedWord.count() < _viewedWordCount){
                _viewedWord.insert(word, wordCount);
                continue;
            }

            if(_viewedWord.contains(word)){
                _viewedWord.insert(word, wordCount);
                continue;
            }
            QString keyToDelete;
            int minValue = wordCount;
            for(auto it = _viewedWord.begin(); it != _viewedWord.end(); ++it){
                if(it.value() < minValue){
                    keyToDelete = it.key();
                    minValue = it.value();
                }
            }

            if(!keyToDelete.isEmpty()){
                _viewedWord.remove(keyToDelete);
                _viewedWord.insert(word, wordCount);
            }
        }
        // ----- progress -----
        if(wordReaded > _blockWordCont){
            wordReaded = 0;

            int percent = static_cast<int>((_stream->pos() * 100) / _fileSize);

            emit sigPercent(percent);
            emit sigState(_viewedWord);

            emit sigContinue();
            return;
        }
    }

    _file->close();

    emit sigPercent(100);
    emit sigState(_viewedWord);

    _state = STATEEND;
    emit sigContinue();
}
