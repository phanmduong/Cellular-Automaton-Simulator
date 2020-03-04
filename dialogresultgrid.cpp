#include "dialogresultgrid.h"
#include "ui_dialogresultgrid.h"
#include <QDebug>


void DialogResultGrid::setGrid(Grid *value)
{
    grid = value;
//    for (int j = 0;j<this->grid->getHeight();++j)
//            for (int i = 0; i<this->grid->getWidth();++i){
//             QLabel *label = new QLabel();

//             label->setFixedSize(5,5);

//             label->setMargin(0);
//             label->setIndent(0);
//             label->setStyleSheet(QString::fromStdString("QLabel { background-color : "+ this->grid->getCell(i,j)->getState()->getColor() + ";}"));
//             qDebug() << QString::fromStdString("QLabel { background-color : "+ this->grid->getCell(i,j)->getState()->getColor() + ";}");
//             space.push_back(label);
//             this->ui->layout->addWidget(label, i, j);

//        }
//        this->ui->layout->setHorizontalSpacing(0);
//        this->ui->layout->setVerticalSpacing(0);
}

void DialogResultGrid::drawGrid()
{

}

void DialogResultGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    const int sizeOfCell = 5;

    painter.setPen(QColor("#000000"));
    painter.drawRect(QRect(0,0,this->grid->getWidth()*sizeOfCell,this->grid->getWidth()*sizeOfCell));

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
