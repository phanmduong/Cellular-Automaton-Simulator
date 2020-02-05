#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QLabel*> v;

    for (int i = 0;i<100;++i)
        for (int j = 0; j<100;++j){
         QLabel *label = new QLabel();
         label->setFixedSize(5,5);
         quint32 value = QRandomGenerator::global()->generate();
         if (value %2 == 0){
             label->setStyleSheet("QLabel { background-color : black;}");
         } else {
label->setStyleSheet("QLabel { background-color : white;}");
        }

         label->setMargin(0);
         label->setIndent(0);
         v.push_back(label);
         ui->gridLayout->addWidget(label, i, j);

    }
    ui->gridLayout->setHorizontalSpacing(0);
    ui->gridLayout->setVerticalSpacing(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

