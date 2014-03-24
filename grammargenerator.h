#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QString>
#include <QVector>
#include <QSet>

#include "generatorapi.h"

class GrammarLoader;

class GrammarGenerator
{
public:
    GrammarGenerator();
    ~GrammarGenerator();

    void readGrammar(const QString& _filename);
    void generate(int _depth);
    void clear();

    QString getWord(int _num, int _level = -1) const;
    int wordCount(int _level = -1) const;

    bool isValid() const;

private:
    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

    void separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal);

    void updateCache() const;

private:
    QVector <QSet<Word> > m_unterminalWords; // By levels.
    QVector <QSet<Word> > m_terminalWords;

    int m_currentUpdateVer;

    mutable int m_cacheVer;
    mutable QStringList m_cachedWords;

    GrammarLoader* m_loader;
};

#endif // GRAMMARGENERATOR_H
