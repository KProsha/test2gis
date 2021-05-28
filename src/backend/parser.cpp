#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::parceFile(const QString& parameter) {
    QString result;
    /* ... here is the expensive or blocking operation ... */
//    emit s(result);
}
