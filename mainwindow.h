#ifndef ROOF_H
#define ROOF_H

#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include "flowpainter.h"
#include "roofui/roofimagedelegate.h"
#include "roofui/roofimagesmodel.h"
#include "grammarperformer/grammarperformer.h"

namespace Ui
{
    class roof;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadPainter();
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

private:
    BasePainter *painter;
    Ui::roof *ui;
    RoofImageDelegate *imageDelegate;
    RoofImagesModel *model;
};

#endif // ROOF_H
