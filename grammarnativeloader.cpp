#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "grammarnativeloader.h"
#include "rule.h"

const QChar commentator = '#';

GrammarNativeLoader::GrammarNativeLoader()
    : GrammarLoader(),
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
        return _line.split(" ");
    }
    return QStringList();
}

void GrammarNativeLoader::parceGrammar(const QString& _filename)
{
    QFile data(_filename);
    if (data.open(QFile::ReadOnly))
    {
        m_isValid = true;
        qDebug() << "file opend!";
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

Word GrammarNativeLoader::startWord() const
{
    return m_startWord;
}

bool GrammarNativeLoader::isValid() const
{
    return m_isValid;
}
