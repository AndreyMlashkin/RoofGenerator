#ifndef TESTGRAMMAR_H
#define TESTGRAMMAR_H

#include <QObject>

class TestGrammar : public QObject
{
    Q_OBJECT
public:
    explicit TestGrammar(QObject *_parent = 0);

signals:

private slots:
    void testLoader();
};

#endif // TESTGRAMMAR_H
