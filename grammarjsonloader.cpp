#include "grammarjsonloader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

GrammarJsonLoader::GrammarJsonLoader(): m_isValid(0)
{
}

void GrammarJsonLoader::parceGrammar(const QString &_filename)
{
    QFile jsonFile(_filename);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        m_isValid = 0;
        return;
    }
    QJsonParseError error;
    QByteArray saveData = jsonFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));
    if(error.error != QJsonParseError::NoError){
        qDebug()<<error.errorString();
        m_isValid = 0;
        return;
    }
    QJsonObject json = loadDoc.object();
    QJsonArray nonTerminal = json["nonterminal"].toArray();
    foreach(const QJsonValue &elem, nonTerminal){
        m_unterminalSymbols.append(elem.toString());
    }
    QJsonArray terminal = json["terminal"].toArray();
    foreach(const QJsonValue &elem, terminal){
        m_terminalSymbols.append(elem.toString());
    }
    QJsonArray start = json["start"].toArray();
    foreach(const QJsonValue &elem, start){
        m_startWords.append(elem.toString());
    }
    QJsonObject rules = json["rules"].toObject();
    foreach(const QString &key, rules.keys()){
        QJsonObject rules = rules[key].toString();
    }
    m_isValid = 1;
}

QStringList GrammarJsonLoader::unterminalSymbols() const
{
    return m_unterminalSymbols;
}

QStringList GrammarJsonLoader::terminalSymbols() const
{
    return m_terminalSymbols;
}

QVector<Rule *> GrammarJsonLoader::rules() const
{
    return m_rules;
}

QStringList GrammarJsonLoader::startWords() const
{
    return m_startWords;
}

bool GrammarJsonLoader::isValid() const
{
    return m_isValid;
}
