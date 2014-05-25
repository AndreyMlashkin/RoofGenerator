#include <QPainter>
#include <QDebug>
#include <QImage>

#include "roofimage.h"

RoofImage::RoofImage()
    : m_image(NULL),
      m_level(-1)
{}

RoofImage::~RoofImage()
{
    if(!m_image->isNull())
        delete m_image;
}

RoofImage::RoofImage(QImage* _image, int _level, QString _rawString)
    : m_image(_image),
      m_level(_level),
      m_rawString(_rawString)
{
//    qDebug()<<_image<<_level<<_rawString;
}

QImage *RoofImage::getImage() const
{
    return m_image;
}

void RoofImage::setImage(QImage *value)
{
    m_image = value;
}
int RoofImage::getLevel() const
{
    return m_level;
}

void RoofImage::setLevel(int value)
{
    m_level = value;
}
QString RoofImage::getRawString() const
{
    return m_rawString;
}

void RoofImage::setRawString(const QString &value)
{
    m_rawString = value;
}

