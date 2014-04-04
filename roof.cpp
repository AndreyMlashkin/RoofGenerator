#include "roof.h"
#include "ui_roof.h"
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsItem>

roof::roof(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roof)
{
    ui->setupUi(this);
    painter = new FlowPainter;
    painter->loadBlocks(":data/blocks.json");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setSceneRect(0,0, 300, 450);
    scene->setSceneRect(0,0,300,450);

    ui->graphicsView->scale(0.8,0.8);
}

void roof::paintRoof(QString roofBase)
{
    painter->paint(roofBase, scene);

    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    scene->setSceneRect(scene->itemsBoundingRect());
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);

    QString fileName = QString("d:\\projects\\cpp\\testQML\\img\\")+QString::number(rand())+".png";
    image.save(fileName);
}

roof::~roof()
{
    delete painter;
    delete scene;
    delete ui;
}
