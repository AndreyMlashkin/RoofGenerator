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

void FlowPainter::paint(QString rawString, QGraphicsScene *scene)
{
    int x = -300, y = 300;

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
}
