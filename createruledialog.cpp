#include "createruledialog.h"
#include "ui_createruledialog.h"

CreateRuleDialog::CreateRuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRuleDialog)
{
    ui->setupUi(this);
}

CreateRuleDialog::~CreateRuleDialog()
{
    delete ui;
}
