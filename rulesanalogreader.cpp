#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "rulesanalogloader.h"
#include "rule.h"

const char commentator = '#';

RulesAnalogReader::RulesAnalogReader()
    : RulesLoader(),
      m_isValid(false)
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
        qDebug() << "contains!";
        return _line.split(" ");
    }
    return QStringList();
}

void RulesAnalogReader::parceGrammar(const QString& _filename)
{
    QFile data(_filename);
    if (data.open(QFile::ReadOnly))
    {
        m_isValid = true;

        QTextStream in(&data);
        QString line;
        do
        {
            line = in.readLine();
            deleteComments(line);

            parceLine(line, "N");
//            if(line.contains(QRegExp("N\\s*=\\s*\\{.*\\}")))
//            {
//                line.remove(QRegExp("N\\s*=\\s*\\{"));
//                line.remove(QRegExp("\\}.*$"));
//                qDebug() << "contains!";
//            }

//            qDebug() << line;
        }
        while (!line.isNull());
    }
    else
    {
        qDebug() << "No rules file! " << _filename << "in " << Q_FUNC_INFO;
        m_isValid = false;
    }
}

QStringList RulesAnalogReader::unterminalSymbols() const
{
    return m_unterminalSymbols;
}

QStringList RulesAnalogReader::terminalSymbols() const
{
    return m_terminalSymbols;
}

QVector<Rule *> RulesAnalogReader::rules() const
{
    return m_rules;
}

Word RulesAnalogReader::startWord() const
{
    return m_startWord;
}

bool RulesAnalogReader::isValid() const
{
    return m_isValid;
}
