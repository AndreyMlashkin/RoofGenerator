#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSet>

#include "generatorapi.h"

class GrammarLoader;
class WordsGenerator;

class GrammarGenerator : public QObject
{
    Q_OBJECT
public:
    GrammarGenerator();
    ~GrammarGenerator();

    void readGrammar(const QString& _filename);
    void beginGenerate(int _level);
    bool isValid() const;

    void reset();
    bool isNextWord();
    Word nextWord();

private slots:
    void generatorFinished();

private:
    void generate(int _level, const Word& _word);

    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

    void merge(QVector <QSet<Word> > _words);

    void separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal);

    bool isTerminal(const Word& _word);

private:
    int m_maxLevel;

    QVector <QSet<Word> > m_unterminalWords; // By levels.
    QVector <QSet<Word> > m_terminalWords;

    int m_currentWordNum;

    GrammarLoader* m_loader;
    WordsGenerator* m_generator;
};

#endif // GRAMMARGENERATOR_H
