#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <simulation.h>
#include <configuration.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Simulation *simulation;
    Configuration *config;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_heightEdit_textChanged(const QString &arg1);

    void on_widthEdit_textChanged(const QString &arg1);

    void on_numberOfStateEdit_textChanged(const QString &arg1);

    void on_limitGenerationEdit_textChanged(const QString &arg1);

    void on_neighborsEdit_textChanged();

    void on_rulesComboBox_currentIndexChanged(const QString &arg1);

    void on_launchButton_clicked();

    void on_chooseFileRule_clicked();

    void on_chooseFileInput_clicked();

    void on_chooseDirOutput_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
