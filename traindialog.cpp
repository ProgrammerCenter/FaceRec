#include "traindialog.h"
#include "ui_traindialog.h"

TrainDialog::TrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainDialog)
{
    ui->setupUi(this);
    this->setModal(true);
}

void TrainDialog::changeProgress(int n) {
    this->ui->progressBar->setValue(n);
}

void TrainDialog::changeState(QString state) {
    this->ui->label_2->setText(state);
}

TrainDialog::~TrainDialog()
{
    delete ui;
}
