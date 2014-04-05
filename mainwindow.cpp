#include "mainwindow.h"
#include "ui_roof.h"
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roof)
{
    ui->setupUi(this);
    imageDelegate = new RoofImageDelegate;
    model = new RoofImagesModel;
    ui->listView->setItemDelegate(imageDelegate);
    ui->tableView->setItemDelegate(imageDelegate);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);

    loadPainter();
}

void MainWindow::loadPainter()
{
    painter = new FlowPainter;
    painter->loadBlocks(":data/blocks.json");
}

MainWindow::~MainWindow()
{
    delete painter;
    delete model;
    delete imageDelegate;
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    GrammarPerformer g;

    g.readGrammar("://data/rules.json");
    qDebug() << g.isValid();

    g.beginGenerate(5);

    while(g.isNextWord())
    {
        QString generated = g.nextWord();
        qDebug() << generated;
        if(generated.isEmpty())
            continue;
//        ui->label->setPixmap(((QPixmap::fromImage(*painter->paintImage(generated)))));

        model->addItem(new RoofImage(painter->paintImage(generated), 1));
    }
}
