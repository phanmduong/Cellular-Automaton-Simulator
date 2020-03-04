#ifndef DIALOGRESULTGRID_H
#define DIALOGRESULTGRID_H
#include <grid.h>
#include <QDialog>

namespace Ui {
class DialogResultGrid;
}

class DialogResultGrid : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResultGrid(QWidget *parent = nullptr);
    ~DialogResultGrid();

private:
    Ui::DialogResultGrid *ui;
    void rawGird();
};

#endif // DIALOGRESULTGRID_H
