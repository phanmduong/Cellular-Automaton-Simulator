#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>


void MainWindow::getItemRule()
{
    this->simulation->getRulesFromFile(this->config->getFileRulePath());
    vector<Rule *> rules = this->simulation->getRules();
    this->ui->rulesComboBox->clear();
    for(int i = 0; i< rules.size(); ++i){
        this->ui->rulesComboBox->addItem(QString::fromStdString(rules[i]->getName()));
    }
}

void MainWindow::getInitialValue()
{
     this->config->setHeight(this->ui->heightEdit->text().toInt());
    this->config->setWidth(this->ui->widthEdit->text().toInt());
    this->config->setNumberOfState(this->ui->numberOfStateEdit->text().toInt());
    this->config->setLimitGeneration(this->ui->limitGenerationEdit->text().toInt());
    this->config->setNeighborPostionText(this->ui->neighborsEdit->toPlainText().toStdString());
    this->config->setRuleName(this->ui->rulesComboBox->currentText().toStdString());
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->progressBar->hide();
    this->config = new Configuration();
    this->simulation = new Simulation(this->config);

    this->simulation->moveToThread(&this->simulationThread);

    connect(&this->simulationThread,&QThread::started, this, &MainWindow::on_started_simulation);
    connect(this, &MainWindow::start_simulation, this->simulation, &Simulation::run);
    connect(this->simulation, &Simulation::progressChanged, this, &MainWindow::on_progress_change);
    connect(this->simulation, &Simulation::finished, this, &MainWindow::on_finished_simulation);

    this->getItemRule();
    this->getInitialValue();
    qDebug() << QString::fromStdString(to_string(this->config->getWidth()));
    qDebug() << QString::fromStdString(to_string(this->config->getHeight()));
    qDebug() << QString::fromStdString(to_string(this->config->getNumberOfState()));
    qDebug() << QString::fromStdString(to_string(this->config->getLimitGeneration()));
    qDebug() << QString::fromStdString(this->config->getNeighborPostionText());
}

MainWindow::~MainWindow()
{
    this->simulationThread.quit();
    this->simulationThread.wait();
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
    this->simulationThread.start();
    emit start_simulation();
}

void MainWindow::on_chooseFileRule_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose file rule");

    this->ui->ruleFilePathEdit->setText(file_name);

    this->config->setFileRulePath(file_name.toStdString());
    this->getItemRule();
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

void MainWindow::on_progress_change(float value)
{
    this->ui->progressBar->setValue((int) value);
}

void MainWindow::on_started_simulation()
{
    this->disabledUI(true);
    this->ui->progressBar->show();
}

void MainWindow::on_finished_simulation()
{
    this->disabledUI(false);
    this->ui->progressBar->hide();
    this->simulationThread.quit();
}

void MainWindow::disabledUI(bool value){
     this->ui->launchButton->setDisabled(value);
    this->ui->chooseFileInput->setDisabled(value);
    this->ui->chooseDirOutput->setDisabled(value);
    this->ui->chooseFileRule->setDisabled(value);
    this->ui->heightEdit->setDisabled(value);
    this->ui->widthEdit->setDisabled(value);
    this->ui->limitGenerationEdit->setDisabled(value);
    this->ui->numberOfStateEdit->setDisabled(value);
    this->ui->neighborsEdit->setDisabled(value);
    this->ui->rulesComboBox->setDisabled(value);
}
