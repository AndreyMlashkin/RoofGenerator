#ifndef ELEMENTARYBLOCK_H
#define ELEMENTARYBLOCK_H

class QPixmap;
#include <QString>

class ElementaryBlock
{
public:
    ElementaryBlock(QString uri, QString _character, int _levelChange);
    ElementaryBlock(const ElementaryBlock& _block);
    ~ElementaryBlock();

    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    int getLevelChange() const;
    void setLevelChange(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

private:
    QPixmap* image;
    QString character;
    int levelChange;
    int width;
    int height;
};

#endif // ELEMENTARYBLOCK_H
