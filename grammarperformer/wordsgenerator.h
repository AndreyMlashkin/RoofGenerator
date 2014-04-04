#ifndef WORDSGENERATOR_H
#define WORDSGENERATOR_H

#include <QObject>
#include <QVector>
#include <QSet>
#include "generatorapi.h"

class GrammarLoader;

class WordsGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WordsGenerator(GrammarLoader* _loader);
    void begin(int _level);
    bool isValid() const;

    const QVector <QSet<Word> > generatedWords() const;

signals:
    void finished();

private:
    void generate(int _level, const Word& _word);

private:
    bool isFinished;
    int m_maxLevel;
    GrammarLoader* m_loader;
    QVector <QSet<Word> > m_generatedWords;
};

#endif // WORDSGENERATOR_H
