#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QList>
#include <QVector>
#include <QString>
#include <QStringList>

class Grammar
{
public:
    Grammar(const QList<QString>& _n, const QList<QString>& _t, const QStringList& _p, const QStringList& _s);

private:
    const QList<QString> m_n, m_t;// Терминальные и не терминальные символы.

    const QStringList m_p;
};

#endif // GRAMMAR_H
