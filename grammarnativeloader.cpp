#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "grammarnativeloader.h"
#include "rule.h"

const QChar commentator = '#';

GrammarNativeLoader::GrammarNativeLoader()
    : GrammarLoader(),
      m_untermParsed(false),
      m_rulesParsed(false),
      m_terminalParsed(false),
      m_startWordParsed(false)
{
}

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

inline QString parseRulesLine(QString _line)
{

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
                m_unterminalSymbols = parceLine(line, "N");
                if(!m_unterminalSymbols.isEmpty())
                {
                    m_untermParsed = true;
                    continue;
                }
            }
            if(!m_terminalParsed)
            {
                m_terminalSymbols = parceLine(line, "T");
                if(!m_unterminalSymbols.isEmpty())
                {
                    m_terminalParsed = true;
                    continue;
                }
            }
            if(!m_startWordParsed)
            {
                m_startWords = parceLine(line, "S");
                if(!m_startWords.isEmpty())
                {
                    m_startWordParsed = true;
                    continue;
                }
            }
        }
        while (!line.isNull());
    }
    else
    {
        qDebug() << "No rules file! " << _filename << "in " << Q_FUNC_INFO;
    }
}

QStringList GrammarNativeLoader::unterminalSymbols() const
{
    return m_unterminalSymbols;
}

QStringList GrammarNativeLoader::terminalSymbols() const
{
    return m_terminalSymbols;
}

QVector<Rule *> GrammarNativeLoader::rules() const
{
    return m_rules;
}

QStringList GrammarNativeLoader::startWords() const
{
    return m_startWords;
}

bool GrammarNativeLoader::isValid() const
{
    return m_untermParsed && m_rulesParsed && m_terminalParsed && m_startWordParsed;
}
