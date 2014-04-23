#include "mainwindow.h"
#include "ui_roof.h"
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsItem>
#include <QDebug>
#include <QFile>

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

    connect(this, SIGNAL(mySizeChanged(int)), model, SLOT(updateColumnByWidth(int)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), SLOT(clickTableElement(QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), SLOT(clickTableElement(QModelIndex)));

    loadPainter();
    on_loadButton_clicked();
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
    updateTable();
    ui->loadButton->setEnabled(false);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    updateTable();
}

void MainWindow::updateTable()
{
    emit mySizeChanged(ui->tableView->width()-20);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::clickTableElement(const QModelIndex &index)
{
    RoofImage* roof = reinterpret_cast<RoofImage*>(index.internalPointer());
    if (roof){
        ui->label->setPixmap(QPixmap::fromImage(*(roof->getImage())));
    }
    RoofImagesModel *model = dynamic_cast<RoofImagesModel*>(ui->listView->model());
    if(model->getState() == RoofImagesModel::TABLE)
        on_backButton_clicked();
}

void MainWindow::on_backButton_clicked()
{
    RoofImagesModel *model = qobject_cast<RoofImagesModel*>(ui->listView->model());
    if(ui->stackedWidget->currentIndex() == 0){
//        updateTable();
        model->changeMode();
        ui->stackedWidget->setCurrentIndex(1);
        ui->backButton->setEnabled(true);
    }else{
        model->changeMode();
        ui->stackedWidget->setCurrentIndex(0);
        ui->backButton->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFile File("style.qss");
    if(!File.open(QFile::ReadOnly)){
        File.setFileName(":/style.qss");
        File.open(QFile::ReadOnly);
    }
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}
