#ifndef ROOF_H
#define ROOF_H

#include <QWidget>
#include <QString>

#include "ui_askDialog.h"
#include "ui_ownDraw.h"

namespace Ui
{
    class roof;
}

class BasePainter;
class RoofImageDelegate;
class RoofImagesModel;
class ListToTableProxy;
class GrammarPerformer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadPainter();

public slots:
    void clickTableElement(const QModelIndex &index);

signals:
    void mySizeChanged(int size);

private slots:
    void on_loadButton_clicked();
    void on_backButton_clicked();
    void reloadCss();

    void fillModelByGenerator(int level = 6, int styleNum = 1);

    void on_ownDrawOpen_clicked();
    void drawOwnRoof();

private:
    void resizeEvent(QResizeEvent*);
    void updateTable();
    void initOwnDrawDialog();

private:
    QVector<BasePainter *> painters;
    Ui::roof *ui;

    RoofImageDelegate *imageDelegate;
    RoofImagesModel *model;
    ListToTableProxy *proxyModel;

    Ui_askDialog *askUi;
    QDialog *askDialog;

    Ui_ownDrawDialog *ownDrawUi;
    QDialog *ownDrawDialog;
};

#endif // ROOF_H
