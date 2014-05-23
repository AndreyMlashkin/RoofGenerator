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
    void begin();
    void begin(int _level);
    void setLevel(int _level);

    bool isValid() const;

    const QVector <QSet<Word> > generatedWords() const;

    bool isFinished() const;
//signals:
//    void finished();

private:
    void generate(int _level, const Word& _word);

private:
    bool m_isFinished;
    int m_maxLevel;
    int m_level;
    GrammarLoader* m_loader;
    QVector <QSet<Word> > m_generatedWords;
};

#endif // WORDSGENERATOR_H
