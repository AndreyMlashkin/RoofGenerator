#ifndef ROOFIMAGE_H
#define ROOFIMAGE_H
#include <QMetaType>
#include <QImage>
#include <QString>
class RoofImage
{
public:
    RoofImage();
    ~RoofImage();

    RoofImage(QImage * _image, int _level, QString _rawString = "");
    QImage *getImage() const;
    void setImage(QImage *value);

    int getLevel() const;
    void setLevel(int value);
    QString getRawString() const;
    void setRawString(const QString &value);

private:
    QImage *image;
    int level;
    QString rawString;
};

Q_DECLARE_METATYPE(RoofImage)

#endif // ROOFIMAGE_H
