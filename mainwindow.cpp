#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


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
    this->config->setLimitGeneration(this->ui->limitGenerationEdit->text().toInt());
    this->config->setIntervalTime(this->ui->intervalTimeEdit->text().toInt());
    this->config->setNeighborPostionText(this->ui->neighborsEdit->toPlainText().toStdString());
    this->config->setRuleName(this->ui->rulesComboBox->currentText().toStdString());
}

bool MainWindow::validateForm()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");

    if (this->config->getWidth() <= 0){

        msgBox.setText("Width invalid");
        msgBox.exec();
        return false;
    }

    //TODO: ....

    return true;
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
//    this->getItemRule();

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
    if (!this->validateForm()) return;
    this->simulationThread.start();
    emit start_simulation();
}

void MainWindow::on_chooseFileRule_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose file rule");

    this->ui->ruleFilePathEdit->setText(file_name);

    this->config->setFileRulePath(file_name.toStdString());
    if (file_name == "") return;
    this->getItemRule();
}

void MainWindow::on_chooseFileInput_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Choose input value file");

    this->ui->inputFilePathEdit->setText(file_name);

    this->config->setFileInputValuePath(file_name.toStdString());

    if (file_name == "") return;

    this->config->getConfigFromFile(file_name.toStdString());
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
//    this->hide();
}

void MainWindow::on_finished_simulation()
{
    qDebug() << "end";
    this->disabledUI(false);
    disconnect(this->simulation->getGrid(), &Grid::rule_error, this, &MainWindow::on_rule_error);
    this->simulationThread.quit();
    this->simulationThread.wait();
    this->resultDialog->hideProgress();
}

void MainWindow::on_started_generation()
{
    qDebug() << "generation";
    connect(this->simulation->getGrid(), &Grid::rule_error, this, &MainWindow::on_rule_error);
    this->resultDialog->setGrid(this->simulation->getGrid());
    this->resultDialog->show();
    this->resultDialog->showProgress();
}

void MainWindow::disabledUI(bool value){
     this->ui->launchButton->setDisabled(value);
    this->ui->chooseFileInput->setDisabled(value);
    this->ui->chooseDirOutput->setDisabled(value);
    this->ui->chooseFileRule->setDisabled(value);
    this->ui->limitGenerationEdit->setDisabled(value);
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
    this->simulation->quit();
    this->resultDialog->hide();
    this->show();
}

void MainWindow::on_pause_progress()
{
    if (this->simulation->getIsPause() == true){
        this->simulation->setIsPause(false);
    } else {
        this->simulation->setIsPause(true);
    }

}

void MainWindow::on_rule_error(QString message)
{
    qDebug() << "error";
    this->on_diablog_result_close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText("Rule Error: "+ message);
    msgBox.exec();



}

void MainWindow::on_message(QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Message");
    msgBox.setText(message);
    msgBox.exec();

}
