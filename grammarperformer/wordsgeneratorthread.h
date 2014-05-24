#ifndef WORDSGENERATORTHREAD_H
#define WORDSGENERATORTHREAD_H

#include <QThread>
#include <QMutex>
#include "generatorapi.h"

class WordsGenerator;
class GrammarLoader;

class WordsGeneratorThread : public QThread
{
    Q_OBJECT
public:
    WordsGeneratorThread();
    WordsGeneratorThread(GrammarLoader* _loader);
    ~WordsGeneratorThread();

    void setGenerator(GrammarLoader* _loader);
    void generateTillLevel(int _level);

    QVector <QSet<Word> > result() const;

private:
    void run();

private:
    WordsGenerator* m_generator;
    QMutex m_mutex;
};

#endif // WORDSGENERATORTHREAD_H
