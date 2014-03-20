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

    painter->paint("/--/-\\/\\-|/|\\/|-\\|-\\", scene);
    ui->graphicsView->scale(0.8,0.8);
}

roof::~roof()
{
    delete painter;
    delete scene;
    delete ui;
}
