#ifndef BASEPAINTER_H
#define BASEPAINTER_H

#include <QMap>
#include <QString>
#include <QGraphicsScene>

class ElementaryBlock;
class QPainter;

class BasePainter
{
public:
    BasePainter(){}
    virtual ~BasePainter();

    virtual void paint(QString rawString, QGraphicsScene* scene) = 0;
    int loadBlocks(QString blockFile);
private:
    bool check();
protected:
    int currentLevel;
    int currentElem;
    QMap<QString, ElementaryBlock*> blockList;
};

#endif // BASEPAINTER_H
