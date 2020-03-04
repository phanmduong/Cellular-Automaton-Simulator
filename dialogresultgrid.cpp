#include "dialogresultgrid.h"
#include "ui_dialogresultgrid.h"

DialogResultGrid::DialogResultGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogResultGrid)
{
    ui->setupUi(this);
}

DialogResultGrid::~DialogResultGrid()
{
    delete ui;
}
