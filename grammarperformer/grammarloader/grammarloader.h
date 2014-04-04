#ifndef RULESLOADER_H
#define RULESLOADER_H

#include <QStringList>
#include <QVector>

class Rule;
class GrammarLoaderPrivate;

class GrammarLoader
{
public:
    GrammarLoader();
    virtual ~GrammarLoader();
    virtual GrammarLoader* clone() = 0;

    virtual void parceGrammar(const QString&) = 0;

    void setStartWords(const QStringList& _words);
    QStringList startWords() const;
    QStringList unterminalSymbols() const;
    QStringList terminalSymbols() const;
    const QVector <Rule*> rules() const;

    bool isValid() const;

protected:
    GrammarLoaderPrivate* p;

private:
    GrammarLoader(const GrammarLoader&);
    GrammarLoader& operator =(const GrammarLoader& _loader);
};

#endif // GrammarLoader_H
