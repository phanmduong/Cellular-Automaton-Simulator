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
    this->config->setIntervalTime(this->ui->intervalTimeEdit->text().toInt());
    this->config->setNeighborPostionText(this->ui->neighborsEdit->toPlainText().toStdString());
    this->config->setRuleName(this->ui->rulesComboBox->currentText().toStdString());
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->resultDialog = new DialogResultGrid();
    this->config = new Configuration();
    this->simulation = new Simulation(this->config);

    this->simulation->moveToThread(&this->simulationThread);

    connect(&this->simulationThread,&QThread::started, this, &MainWindow::on_started_simulation);
    connect(this, &MainWindow::start_simulation, this->simulation, &Simulation::run);
    connect(this->simulation, &Simulation::startGeneration, this, &MainWindow::on_started_generation);
    connect(this->simulation, &Simulation::progressChanged, this, &MainWindow::on_progress_change);
    connect(this->simulation, &Simulation::finished, this, &MainWindow::on_finished_simulation);
    connect(this->resultDialog, &DialogResultGrid::finished, this, &MainWindow::on_diablog_result_close);
    connect(this->resultDialog, &DialogResultGrid::pause_simulation, this, &MainWindow::on_pause_progress);

    this->getItemRule();

    this->getInitialValue();
}

MainWindow::~MainWindow()
{
    this->simulationThread.quit();
    this->simulationThread.wait();
    delete simulation;
    delete config;
    delete ui;
    delete resultDialog;
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
    this->resultDialog->repaint();
    this->resultDialog->updateProgress(value);
}

void MainWindow::on_started_simulation()
{
    qDebug() << "start";
    this->disabledUI(true);
    this->hide();
}

void MainWindow::on_finished_simulation()
{
    qDebug() << "end";
    this->disabledUI(false);
    this->simulationThread.quit();
    this->resultDialog->hideProgress();
}

void MainWindow::on_started_generation()
{
    qDebug() << "generation";
    this->resultDialog->setGrid(this->simulation->getGrid());
    this->resultDialog->show();
    this->resultDialog->showProgress();
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
    this->ui->intervalTimeEdit->setDisabled(value);
}

void MainWindow::on_intervalTimeEdit_textChanged(const QString &arg1)
{
    this->config->setIntervalTime(arg1.toInt());
}

void MainWindow::on_diablog_result_close()
{
    this->show();
    this->simulation->quit();
    this->simulationThread.quit();
    this->simulationThread.wait();
}

void MainWindow::on_pause_progress()
{
    if (this->simulation->getIsPause() == true){
        this->simulation->setIsPause(false);
    } else {
        this->simulation->setIsPause(true);
    }

}
