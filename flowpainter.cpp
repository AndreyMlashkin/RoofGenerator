#include "flowpainter.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include "elementaryblock.h"

FlowPainter::FlowPainter()
{
}

int border(int level){
    if(level>=1)
        return 1;
    if(level<=-1)
        return -1;
    return 0;
}

QGraphicsScene* FlowPainter::paint(QString rawString)
{
    if(!isLoad)
        return NULL;
    QGraphicsScene* scene = new QGraphicsScene;
//    scene->setSceneRect(0,0,300,450);

    int x = -150, y = 300;

    int i = 0, length = rawString.length(), realLevel = 0;
    ElementaryBlock *prev = NULL;
    QString block;
    while(i<length){
        block = rawString[i];
        if(i<length-1){
            if(rawString[i+1] == '|'){
                block.append("|");
                i++;
            }
        }
        if(!blockList.contains(block))
            continue;
        QGraphicsPixmapItem* item = scene->addPixmap(*(blockList[block]->getImage()));
        if(prev == NULL)
            prev = blockList[block];
        else{
            if((prev->getLevelChange() == -1 && blockList[block]->getLevelChange() == 0) ||
                (prev->getLevelChange() == 0 && blockList[block]->getLevelChange() == 1)){

            }else if(prev->getLevelChange() == 0 && blockList[block]->getLevelChange() == -1)
                y +=blockList[block]->getHeight();
            else{
                realLevel = border(prev->getLevelChange() + blockList[block]->getLevelChange());
                y += blockList[block]->getHeight()*realLevel*(-1);
            }
        }
        prev = blockList[block];

        item->setPos(x, y);
        x += blockList[block]->getWidth();

        i++;
    }
    return scene;
}

QImage *FlowPainter::paintImage(QString rawString)
{
    QGraphicsScene* scene = paint(rawString);
    if(scene == NULL)
        return NULL;
    QImage *image = new QImage(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    scene->setSceneRect(scene->itemsBoundingRect());
    QPainter painter(image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    delete scene;
    return image;
}
