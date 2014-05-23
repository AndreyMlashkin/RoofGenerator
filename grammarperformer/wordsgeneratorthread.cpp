#include <QDebug>
#include <QMutexLocker>
#include <QCoreApplication>

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
    QMutexLocker locker(&m_mutex);
    delete m_generator;
}

void WordsGeneratorThread::setGenerator(WordsGenerator* _generator)
{
    QMutexLocker locker(&m_mutex);
    delete m_generator;
    m_generator = _generator;
}

void WordsGeneratorThread::generateTillLevel(int _level)
{
    m_generator->setLevel(_level);
    m_generator->moveToThread(this);
    qDebug() << "start thread: " << thread();
    start();
}

QVector<QSet<Word> > WordsGeneratorThread::result() const
{
    return m_generator->generatedWords();
}

void WordsGeneratorThread::run()
{
    if(!m_generator->isFinished())
    {
        m_generator->begin();
        m_generator->moveToThread(qApp->thread());
    }
    exit();
}
