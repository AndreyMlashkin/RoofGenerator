#include <QDebug>
#include <QMutexLocker>
#include <QCoreApplication>

#include "wordsgeneratorthread.h"
#include "wordsgenerator.h"

WordsGeneratorThread::WordsGeneratorThread()
    : m_generator(NULL)
{}

WordsGeneratorThread::WordsGeneratorThread(GrammarLoader* _loader)
    : m_generator(new WordsGenerator(_loader))
{}

WordsGeneratorThread::~WordsGeneratorThread()
{
    QMutexLocker locker(&m_mutex);
    delete m_generator;
}

void WordsGeneratorThread::setGenerator(GrammarLoader* _loader)
{
    QMutexLocker locker(&m_mutex);
    delete m_generator;
    m_generator = new WordsGenerator(_loader);
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
