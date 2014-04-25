#ifndef ROOF_H
#define ROOF_H

#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include "flowpainter.h"
#include "roofui/roofimagedelegate.h"
#include "roofui/roofimagesmodel.h"
#include "roofui/listtotableproxy.h"
#include "grammarperformer/grammarperformer.h"
#include "ui_askDialog.h"

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
public slots:
    void clickTableElement(const QModelIndex &index);
signals:
    void mySizeChanged(int size);
private slots:
    void on_loadButton_clicked();

    void on_backButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void fillModelByGenerator(int level = 6, int styleNum = 1);

private:
    QVector<BasePainter *> painters;
    Ui::roof *ui;

    RoofImageDelegate *imageDelegate;
    RoofImagesModel *model;
    ListToTableProxy *proxyModel;

    Ui_askDialog *askUi;
    QDialog *askDialog;

    void resizeEvent(QResizeEvent*);
    void updateTable();
};

#endif // ROOF_H
