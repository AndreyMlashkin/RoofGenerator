#include "roofimage.h"
#include <QPainter>
#include <QDebug>

RoofImage::RoofImage() :
    image(NULL)
{
    qDebug()<< Q_FUNC_INFO;
}

RoofImage::~RoofImage()
{
    delete image;
}

RoofImage::RoofImage(QImage* _image, int _level):
    image(_image), level(_level)
{
}

QImage *RoofImage::getImage() const
{
    return image;
}

void RoofImage::setImage(QImage *value)
{
    image = value;
}
int RoofImage::getLevel() const
{
    return level;
}

void RoofImage::setLevel(int value)
{
    level = value;
}
