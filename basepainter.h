#ifndef BASEPAINTER_H
#define BASEPAINTER_H

#include <QMap>
#include <QChar>

class ElementaryBlock;
class QPainter;

class BasePainter
{
public:
    BasePainter(){};
    BasePainter(QString blockFile);
    ~BasePainter();


    virtual void paint(QPainter* painter) = 0;
    int loadBlocks(QString blockFile);
private:
    bool check();


    int currentLevel;
    int currentElem;
    QMap<QChar, ElementaryBlock*> blockList;
};

#endif // BASEPAINTER_H
