#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <simulation.h>
#include <configuration.h>
#include <QThread>
#include <dialogresultgrid.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DialogResultGrid *resultDialog;
    Simulation *simulation;
    Configuration *config;
    QThread simulationThread;

    void getItemRule();
    void getInitialValue();
    bool validateForm();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_limitGenerationEdit_textChanged(const QString &arg1);

    void on_neighborsEdit_textChanged();

    void on_rulesComboBox_currentIndexChanged(const QString &arg1);

    void on_launchButton_clicked();

    void on_chooseFileRule_clicked();

    void on_chooseFileInput_clicked();

    void on_chooseDirOutput_clicked();

    void on_progress_change(float value);

    void on_started_simulation();

    void on_finished_simulation();

    void on_started_generation();

    void on_intervalTimeEdit_textChanged(const QString &arg1);

    void on_diablog_result_close();

    void on_pause_progress();

    void on_rule_error(QString message);

    void on_message(QString message);

signals:
    void start_simulation();

private:
    Ui::MainWindow *ui;

    void disabledUI(bool value);
};
#endif // MAINWINDOW_H
