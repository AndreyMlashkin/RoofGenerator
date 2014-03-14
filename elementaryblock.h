#ifndef ELEMENTARYBLOCK_H
#define ELEMENTARYBLOCK_H
#include <QImage>
class ElementaryBlock
{
public:
    ElementaryBlock(QString uri, QChar _character, int _levelChange);
    ~ElementaryBlock();
private:
    QImage* image;
    QChar character;
    int levelChange;
    int width;
    int height;
};

#endif // ELEMENTARYBLOCK_H
