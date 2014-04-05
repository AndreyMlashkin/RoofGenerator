#ifndef ROOFIMAGE_H
#define ROOFIMAGE_H
#include <QMetaType>
#include <QImage>
class RoofImage
{
public:
    RoofImage();
    ~RoofImage();

    RoofImage(QImage * _image, int _level);
    QImage *getImage() const;
    void setImage(QImage *value);

    int getLevel() const;
    void setLevel(int value);
private:
    QImage *image;
    int level;
};

Q_DECLARE_METATYPE(RoofImage)

#endif // ROOFIMAGE_H
