#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QString>
#include <QVector>
#include "generatorapi.h"

class GrammarLoader;

class GrammarGenerator
{
public:
    GrammarGenerator();
    ~GrammarGenerator();

    void readGrammar(const QString& _filename);
    void generate(int _depth);

    QString getWord(int _num, int _depth = -1) const; // -1 means doesnot matter.
    int wordCount(int _depth = -1) const;

    bool isValid() const;

private:
    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

private:
    QVector <QVector<Word> > m_generatedWords; // by levels.

    GrammarLoader* m_loader;
};

#endif // GRAMMARGENERATOR_H
