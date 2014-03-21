#ifndef ROOF_H
#define ROOF_H

#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include "flowpainter.h"

namespace Ui
{
    class roof;
}

class roof : public QWidget
{
    Q_OBJECT

public:
    explicit roof(QWidget *parent = 0);
    void paintRoof(QString roofBase);
    ~roof();

private:
    BasePainter *painter;
    Ui::roof *ui;
    QGraphicsScene *scene;
};

#endif // ROOF_H
