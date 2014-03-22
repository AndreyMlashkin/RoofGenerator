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
    void generate(int _depth);  // Adds to previous generated words. Use clear() before.
    void clear();

    QString getWord(int _num) const;
    int wordCount() const;

    bool isValid() const;

private:
    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

    void separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal);

private:
    QVector <QSet<Word> > m_unterminalWords; // by levels.
    QSet <QString> m_terminalWords;


    GrammarLoader* m_loader;
};

#endif // GRAMMARGENERATOR_H
