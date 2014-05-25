#include <QPixmap>
#include <QDebug>

#include "elementaryblock.h"

ElementaryBlock::ElementaryBlock(QString uri, QString _character, int _levelChange):
    character(_character), levelChange(_levelChange)
{
    image = new QPixmap(uri);
    if(!image->isNull()){
        width = image->width();
        height = image->height();
    }
}

ElementaryBlock::ElementaryBlock(const ElementaryBlock &_block)
   : image(_block.image),
     character(_block.character),
     levelChange(_block.levelChange),
     width(_block.width),
     height(_block.height)
{}

ElementaryBlock::~ElementaryBlock()
{
    delete image;
}

QPixmap *ElementaryBlock::getImage() const
{
    return image;
}

void ElementaryBlock::setImage(QPixmap *value)
{
    image = value;
}
int ElementaryBlock::getLevelChange() const
{
    return levelChange;
}

void ElementaryBlock::setLevelChange(int value)
{
    levelChange = value;
}
int ElementaryBlock::getWidth() const
{
    return width;
}

void ElementaryBlock::setWidth(int value)
{
    width = value;
}
int ElementaryBlock::getHeight() const
{
    return height;
}

void ElementaryBlock::setHeight(int value)
{
    height = value;
}




