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

public:
    explicit DialogResultGrid(QWidget *parent = nullptr);
    ~DialogResultGrid();

    void setGrid(Grid *value);
    void drawGrid();

    virtual void paintEvent(QPaintEvent *event);
    void repaint();
private:
    Ui::DialogResultGrid *ui;
    void rawGird();
};

#endif // DIALOGRESULTGRID_H
