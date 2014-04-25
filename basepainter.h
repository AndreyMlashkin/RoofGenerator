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
    BasePainter();
    virtual ~BasePainter();

    virtual QGraphicsScene* paint(QString rawString) = 0;
    virtual QImage* paintImage(QString rawString) = 0;
    int loadBlocks(QString blockFile, QString _name = "");
    QString getName();

    bool getIsLoad() const;

private:
    bool check();
protected:
    int currentLevel;
    int currentElem;
    QMap<QString, ElementaryBlock*> blockList;
    bool isLoad;
    QString name;
};

#endif // BASEPAINTER_H
