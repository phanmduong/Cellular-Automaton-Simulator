#ifndef DIALOGRESULTGRID_H
#define DIALOGRESULTGRID_H
#include <grid.h>
#include <QDialog>
#include <QLabel>
#include <QPainter>

namespace Ui {
class DialogResultGrid;
}

class DialogResultGrid : public QDialog
{
    Q_OBJECT
    Grid *grid;
    QVector<QLabel*> space;
    int isPause = false;

public:
    explicit DialogResultGrid(QWidget *parent = nullptr);
    ~DialogResultGrid();

    void setGrid(Grid *value);

    virtual void paintEvent(QPaintEvent *event);
    void repaint();

    void updateProgress(float value);
    void hideProgress();
    void showProgress();

private slots:


    void on_closeButton_clicked();

    void on_pauseButton_clicked();

signals:
    void pause_simulation();

private:
    Ui::DialogResultGrid *ui;

};

#endif // DIALOGRESULTGRID_H
