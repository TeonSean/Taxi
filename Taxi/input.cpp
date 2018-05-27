#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
}

Input::~Input()
{
    delete ui;
}

int Input::getSrc()
{
    return ui->src_input->text().toInt();
}

int Input::getDst()
{
    return ui->dst_input->text().toInt();
}
