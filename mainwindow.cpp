#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->config = new Configuration();
    this->simulation = new Simulation(this->config);


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

void MainWindow::on_chooseFileRule_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose file rule");

    this->ui->ruleFilePathEdit->setText(file_name);

    this->config->setFileRulePath(file_name.toStdString());
    this->simulation->getRulesFromFile(this->config->getFileRulePath());

    vector<Rule *> rules = this->simulation->getRules();
    for(int i = 0; i< rules.size(); ++i){
        this->ui->rulesComboBox->addItem(QString::fromStdString(rules[i]->getName()));
    }
}

void MainWindow::on_chooseFileInput_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose input value file");

    this->ui->inputFilePathEdit->setText(file_name);

    this->config->setFileInputValuePath(file_name.toStdString());
}

void MainWindow::on_chooseDirOutput_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"Choose directory output file");

    this->ui->outputDirPathEdit->setText(path);

    this->config->setDirectoryOutputValuePath(path.toStdString());
}
