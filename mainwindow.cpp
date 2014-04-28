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

    ui->listView->setItemDelegate(imageDelegate);
    ui->tableView->setItemDelegate(imageDelegate);

    model = new RoofImagesModel;
    proxyModel = new ListToTableProxy;
    proxyModel->setSourceModel(model);

    ui->listView->setModel(model);
    ui->tableView->setModel(proxyModel);

    connect(this, SIGNAL(mySizeChanged(int)), proxyModel, SLOT(updateColumnByWidth(int)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), SLOT(clickTableElement(QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), SLOT(clickTableElement(QModelIndex)));
    resizeEvent(NULL);

    loadPainter();
  //  on_loadButton_clicked();

    on_pushButton_clicked();
}

void MainWindow::loadPainter()
{
    for(int i = 1; i<=3;i++){
        BasePainter *p = new FlowPainter;
        p->loadBlocks(QString(":data/style")+QString::number(i)+QString(".json"), QString("Стиль ")+QString::number(i));
        painters.append(p);
    }
}

MainWindow::~MainWindow()
{
    delete model;
    delete imageDelegate;
    delete ui;
    delete askUi;
}

void MainWindow::on_loadButton_clicked()
{
    askDialog = new QDialog(0,0);
    askUi = new Ui_askDialog;
    askUi->setupUi(askDialog);
    foreach(BasePainter* p, painters){
        askUi->styleList->addItem(p->getName());
    }

    if(askDialog->exec()){
        qDebug()<<askUi->styleList->currentIndex();
        fillModelByGenerator(askUi->level->value(), askUi->styleList->currentIndex());
        ui->loadButton->setEnabled(false);
    }
    delete askDialog;
    delete askUi;
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    emit mySizeChanged(ui->tableView->width()-200);
}

void MainWindow::updateTable()
{
    proxyModel->updateTable();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::fillModelByGenerator(int level, int styleNum)
{
    level = level>3 && level<10 ? level : 6;
    styleNum = styleNum<painters.count() ? styleNum : 1;
    GrammarPerformer g;

    g.readGrammar(":data/rules.json");
//    qDebug() << g.isValid();

    g.beginGenerate(level);
    BasePainter *painter = painters[styleNum];
    while(g.isNextWord())
    {
        QString generated = g.nextWord();
//        qDebug() << generated;
        if(generated.isEmpty())
            continue;
        RoofImage *r = new RoofImage(painter->paintImage(generated), 1, generated);
        model->addItem(r);
    }
    qDebug()<<styleNum;
    updateTable();
}

void MainWindow::clickTableElement(const QModelIndex &index)
{
    RoofImage* roof = reinterpret_cast<RoofImage*>(index.internalPointer());
    if (roof){
        ui->label->setPixmap(QPixmap::fromImage(*(roof->getImage())));
        ui->listView->scrollTo(proxyModel->mapToSource(index), QAbstractItemView::PositionAtCenter);
        ui->listView->selectionModel()->select(proxyModel->mapToSource(index), QItemSelectionModel::Select);
    }
    if(ui->stackedWidget->currentIndex() == 0)
        on_backButton_clicked();
}

void MainWindow::on_backButton_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0){
        ui->stackedWidget->setCurrentIndex(1);
        ui->backButton->setEnabled(true);
    }else{
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

void MainWindow::on_pushButton_2_clicked()
{
    proxyModel->updateTable();
}
