#include "roof.h"
#include "ui_roof.h"
#include "flowpainter.h"

roof::roof(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roof)
{
    ui->setupUi(this);
    FlowPainter p;
    p.loadBlocks(":data/blocks.json");
}

roof::~roof()
{
    delete ui;
}
