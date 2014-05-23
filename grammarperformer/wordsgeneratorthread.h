#ifndef WORDSGENERATORTHREAD_H
#define WORDSGENERATORTHREAD_H

#include <QThread>
#include <QMutex>
#include "generatorapi.h"

class WordsGenerator;

class WordsGeneratorThread : public QThread
{
    Q_OBJECT
public:
    WordsGeneratorThread();
    WordsGeneratorThread(WordsGenerator* _generator);
    ~WordsGeneratorThread();

    void setGenerator(WordsGenerator* _generator);
    void generateTillLevel(int _level);

    QVector <QSet<Word> > result() const;

private:
    void run();

private:
    WordsGenerator* m_generator;
    QMutex m_mutex;
};

#endif // WORDSGENERATORTHREAD_H
