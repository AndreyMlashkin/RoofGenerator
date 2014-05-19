#include <QDebug>
#include <QMutexLocker>

#include "wordsgeneratorthread.h"
#include "wordsgenerator.h"

WordsGeneratorThread::WordsGeneratorThread()
    : m_generator(NULL)
{}

WordsGeneratorThread::WordsGeneratorThread(WordsGenerator* _generator)
    : m_generator(_generator)
{}

WordsGeneratorThread::~WordsGeneratorThread()
{
    delete m_generator;
}

void WordsGeneratorThread::setGenerator(WordsGenerator* _generator)
{
    delete m_generator;
    m_generator = _generator;
}

void WordsGeneratorThread::generateTillLevel(int _level)
{
//    qDebug() << isRunning();
    m_generator->moveToThread(this);
    start();
    m_generator->begin(_level);
}

const WordsGenerator* const WordsGeneratorThread::generator() const
{
    return m_generator;
}
