#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "grammarnativeloader.h"
#include "grammarloaderprivate.h"
#include "../rule.h"

const QChar commentator = '#';

GrammarNativeLoader::GrammarNativeLoader()
    : GrammarLoader(),
      m_untermParsed(false),
      m_rulesParsed(false),
      m_terminalParsed(false),
      m_startWordParsed(false)
{}

void inline deleteComments(QString& _str)
{
    _str.remove(QRegExp("#.*$"));
}

QStringList parceLine(QString _line, QString _startLetter)
{
    if(_line.contains(QRegExp(_startLetter + "\\s*=\\s*\\{.*\\}")))
    {
        _line.remove(QRegExp(_startLetter + "\\s*=\\s*\\{"));
        _line.remove(QRegExp("\\}.*$"));
        return _line.split(" ");
    }
    return QStringList();
}

inline QVector <Rule*> parseRules(QString _line, QTextStream& _in)
{
    if(_line.contains(QRegExp("R\\s*=\\s*\\{")))
    {
        QStringList l;
        QVector <Rule*> ans;
        do
        {
            _line = _in.readLine();
            if(!_line.contains("->"))
                continue;
            l = _line.split(" -> ");
            l << " ";
            Rule* r = new Rule(l[0], l[1]);
            ans << r;
        }
        while(!_line.contains("}"));
        return ans;
    }
    return QVector <Rule*>();
}

void GrammarNativeLoader::parceGrammar(const QString& _filename)
{
    m_untermParsed = m_rulesParsed = m_terminalParsed = m_startWordParsed = false;

    QFile data(_filename);
    if (data.open(QFile::ReadOnly))
    {
        QTextStream in(&data);
        QString line;
        do
        {
            line = in.readLine();
            deleteComments(line);

            if(!m_untermParsed)
            {
                p->unterminalSymbols = parceLine(line, "N");
                if(!p->unterminalSymbols.isEmpty())
                {
                    m_untermParsed = true;
                    continue;
                }
            }
            else if(!m_terminalParsed)
            {
                p->terminalSymbols = parceLine(line, "T");
                if(!p->unterminalSymbols.isEmpty())
                {
                    m_terminalParsed = true;
                    continue;
                }
            }
            else if(!m_startWordParsed)
            {
                p->startWords = parceLine(line, "S");
                if(!p->startWords.isEmpty())
                {
                    m_startWordParsed = true;
                    continue;
                }
            }
            else if(!m_rulesParsed)
            {
                p->rules = parseRules(line, in);
                if(!p->rules.isEmpty())
                    m_rulesParsed = true;
            }
        }
        while (!line.isNull());
    }
    else
        qDebug() << "No grammar file! " << _filename << "in " << Q_FUNC_INFO;

    p->isValid = m_untermParsed && m_rulesParsed && m_terminalParsed && m_startWordParsed;
}
