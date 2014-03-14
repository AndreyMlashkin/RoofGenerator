#include "elementaryblock.h"

/*RoofBlock::roofblock()
{
}*/

ElementaryBlock::ElementaryBlock(QString uri, QChar _character, int _levelChange):
    character(_character), levelChange(_levelChange)
{
    image = new QImage(uri);
    if(!image->isNull()){
        width = image->width();
        height = image->height();
    }
}

ElementaryBlock::~ElementaryBlock()
{
    delete image;
}
