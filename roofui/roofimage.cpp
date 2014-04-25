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
    if(!image->isNull())
        delete image;
}

RoofImage::RoofImage(QImage* _image, int _level, QString _rawString):
    image(_image), level(_level), rawString(_rawString)
{
//    qDebug()<<_image<<_level<<_rawString;
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
QString RoofImage::getRawString() const
{
    return rawString;
}

void RoofImage::setRawString(const QString &value)
{
    rawString = value;
}

