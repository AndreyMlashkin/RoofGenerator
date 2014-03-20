#ifndef FLOWPAINTER_H
#define FLOWPAINTER_H

#include "basepainter.h"

class FlowPainter : public BasePainter
{
public:
    FlowPainter();
    void paint(QString rawString, QGraphicsScene *scene);
};

#endif // FLOWPAINTER_H
