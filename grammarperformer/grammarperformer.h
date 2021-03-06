#ifndef GRAMMARGENERATOR_H
#define GRAMMARGENERATOR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSet>

#include "generatorapi.h"

class GrammarLoader;
class WordsGenerator;
class WordsGeneratorThread;

class GrammarPerformer : public QObject
{
    Q_OBJECT
public:
    GrammarPerformer();
    ~GrammarPerformer();
    bool isValid() const;

    void readGrammar(const QString& _filename);
    void beginGenerate(int _level);
    bool isFinished() const;

    void reset();
    bool isNextWord();
    Word nextWord();

private slots:
    void generatorFinished();

private:
    enum LoaderType {Json, Native};
    GrammarLoader* getLoader(LoaderType _type);

    void merge(QVector <QSet<Word> > _words);

    void separateTemAndUnterm(const QVector<Word>& _common, QSet<Word>& _terminal, QSet<Word>& _unterminal);

    bool isTerminal(const Word& _word);

private:
    int m_maxLevel;
    int m_currentWordNum;

    QVector <QSet<Word> > m_unterminalWords; // By levels.
    QVector <QSet<Word> > m_terminalWords;

    QSet <Word> m_clasteredTerminalWords;
    QVector <Word> m_orderedClasteredTerminalWords;

    GrammarLoader* m_loader;

    WordsGeneratorThread* m_generationThread;
    bool m_isFinished;
};

#endif // GRAMMARGENERATOR_H
