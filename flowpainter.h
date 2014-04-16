#ifndef FLOWPAINTER_H
#define FLOWPAINTER_H

#include "basepainter.h"
#include <QGraphicsScene>
#include <QPainter>

class FlowPainter : public BasePainter
{
public:
    FlowPainter();
    QGraphicsScene *paint(QString rawString);
    QImage* paintImage(QString rawString);
};

#endif // FLOWPAINTER_H
