#include "dialogresultgrid.h"
#include "ui_dialogresultgrid.h"
#include <QDebug>


void DialogResultGrid::setGrid(Grid *value)
{
    grid = value;
    isPause = false;
}

void DialogResultGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    const int sizeOfCell = 5;
    const int marginRightWidth = 200;
    this->setFixedSize(sizeOfCell*this->grid->getWidth() + marginRightWidth, sizeOfCell*this->grid->getHeight());
    this->ui->verticalLayoutWidget->setGeometry(sizeOfCell*this->grid->getWidth() + 20, 50, 160, 200);

    painter.setPen(QColor("#000000"));
    painter.drawRect(QRect(0, 0,this->grid->getWidth()*sizeOfCell,this->grid->getWidth()*sizeOfCell));

    for(int i = 0; i< this->grid->getStates().size(); ++i){
        painter.setPen(Qt::white);
        painter.drawText(QPoint(sizeOfCell*this->grid->getWidth() + 100, 300 + i*20), QString::fromStdString("State " + this->grid->getStates()[i]->getName()));
        painter.setPen(QColor("#000000"));
        QColor color(QString::fromStdString(this->grid->getStates()[i]->getColor()));
        painter.setBrush(QBrush(color));
        painter.drawRect(sizeOfCell*this->grid->getWidth() + 80, 290 + i*20, 10, 10);
    }

    painter.setPen(QColor("#000000"));

    for (int j = 0;j<this->grid->getHeight();++j){
        for (int i = 0; i<this->grid->getWidth();++i){
            int topX = j*sizeOfCell;
                        int topY = i*sizeOfCell;
                        QColor color(QString::fromStdString(this->grid->getCell(i,j)->getState()->getColor()));
                        painter.setBrush(QBrush(color));

                        painter.drawRect(topX, topY, sizeOfCell, sizeOfCell);
        }
    }

}

void DialogResultGrid::repaint()
{
    QDialog::repaint();
}

void DialogResultGrid::updateProgress(float value)
{
    this->ui->progressBar->setValue(value);
}

void DialogResultGrid::hideProgress()
{
    this->ui->progressBar->hide();
    this->ui->pauseButton->hide();
}

void DialogResultGrid::showProgress()
{
     this->ui->progressBar->show();
     this->ui->pauseButton->show();
}

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

void DialogResultGrid::on_closeButton_clicked()
{
    this->close();
}

void DialogResultGrid::on_pauseButton_clicked()
{
    if (isPause){
        this->ui->pauseButton->setText("Pause");
        this->isPause = false;
    } else {
        this->ui->pauseButton->setText("Resume");
        this->isPause = true;
    }
    this->pause_simulation();
}
