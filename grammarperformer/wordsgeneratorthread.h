#ifndef WORDSGENERATORTHREAD_H
#define WORDSGENERATORTHREAD_H

#include <QThread>

class WordsGenerator;

class WordsGeneratorThread : public QThread
{
public:
    WordsGeneratorThread();
    WordsGeneratorThread(WordsGenerator* _generator);
    ~WordsGeneratorThread();

    void setGenerator(WordsGenerator* _generator);
    void generateTillLevel(int _level);

    const WordsGenerator* generator() const;

private:
    WordsGenerator* m_generator;
};

#endif // WORDSGENERATORTHREAD_H
