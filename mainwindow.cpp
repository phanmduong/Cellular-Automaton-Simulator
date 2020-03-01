#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->config = new Configuration();
    this->simulation = new Simulation(this->config);

    vector<Rule *> rules = this->simulation->getRules();
    for(int i = 0; i< rules.size(); ++i){
        this->ui->rulesComboBox->addItem(QString::fromStdString(rules[i]->getName()));
    }
}

MainWindow::~MainWindow()
{
    delete simulation;
    delete config;
    delete ui;
}

void MainWindow::on_heightEdit_textChanged(const QString &arg1)
{
    this->config->setHeight(arg1.toInt());
}

void MainWindow::on_widthEdit_textChanged(const QString &arg1)
{
     this->config->setWidth(arg1.toInt());
}

void MainWindow::on_numberOfStateEdit_textChanged(const QString &arg1)
{
    this->config->setNumberOfState(arg1.toInt());
}

void MainWindow::on_limitGenerationEdit_textChanged(const QString &arg1)
{
     this->config->setLimitGeneration(arg1.toInt());
}

void MainWindow::on_neighborsEdit_textChanged()
{
    this->config->setNeighborPostionText(this->ui->neighborsEdit->toPlainText().toStdString());
}

void MainWindow::on_rulesComboBox_currentIndexChanged(const QString &arg1)
{
    this->config->setRuleName(arg1.toStdString());
}

void MainWindow::on_launchButton_clicked()
{
    this->simulation->run();
}
