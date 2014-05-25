#ifndef BASEPAINTER_H
#define BASEPAINTER_H

#include <QMap>
#include <QString>

class ElementaryBlock;
class QPainter;
class QGraphicsScene;
class QImage;

class BasePainter
{
public:
    BasePainter();
    virtual ~BasePainter();

    virtual QGraphicsScene* paint(QString rawString) = 0;
    virtual QImage* paintImage(QString rawString) = 0;
    int loadBlocks(QString blockFile, QString _name = "");
    QString getName() const;

    bool getIsLoad() const;

protected:
    static bool check(QString rawString);

protected:
    int currentLevel;
    int currentElem;
    QMap <QString, ElementaryBlock*> blockList;
    bool isLoad;
    QString name;
};

#endif // BASEPAINTER_H
