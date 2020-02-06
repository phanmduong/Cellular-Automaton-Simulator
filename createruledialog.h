#ifndef CREATERULEDIALOG_H
#define CREATERULEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateRuleDialog;
}

class CreateRuleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRuleDialog(QWidget *parent = nullptr);
    ~CreateRuleDialog();

private:
    Ui::CreateRuleDialog *ui;
};

#endif // CREATERULEDIALOG_H
