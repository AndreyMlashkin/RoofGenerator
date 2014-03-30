#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

#include "grammarjsonloader.h"
#include "grammarloaderprivate.h"
#include "../rule.h"

GrammarJsonLoader::GrammarJsonLoader()
    : GrammarLoader()
{}

GrammarLoader* GrammarJsonLoader::clone()
{
    GrammarJsonLoader* thisClone = new GrammarJsonLoader();
    thisClone->p = new GrammarLoaderPrivate(*p);
    return thisClone;
}

void GrammarJsonLoader::parceGrammar(const QString& _filename)
{
    QFile jsonFile(_filename);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open file.");
        p->isValid = false;
        return;
    }
    QJsonParseError error;
    QByteArray saveData = jsonFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));
    if(error.error != QJsonParseError::NoError){
        qDebug()<<error.errorString();
        p->isValid = false;
        return;
    }
    QJsonObject json = loadDoc.object();
    QJsonArray nonTerminal = json["nonterminal"].toArray();
    foreach(const QJsonValue &elem, nonTerminal){
        p->unterminalSymbols.append(elem.toString());
    }
    QJsonArray terminal = json["terminal"].toArray();
    foreach(const QJsonValue &elem, terminal){
        p->terminalSymbols.append(elem.toString());
    }
    QJsonArray start = json["start"].toArray();
    foreach(const QJsonValue &elem, start){
        p->startWords.append(elem.toString());
    }
    QJsonObject rules = json["rules"].toObject();
    foreach(const QString &key, rules.keys()){
        if(rules[key].isArray()){
            foreach(const QJsonValue &arrayElem, rules[key].toArray()){
                p->rules.append(new Rule(key, arrayElem.toString()));
            }
        }else{
            p->rules.append(new Rule(key, rules[key].toString()));
        }
    }
    p->isValid = true;
}
