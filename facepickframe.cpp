#include "facepickframe.h"
#include "ui_facepickframe.h"

FacePickFrame::FacePickFrame(QWidget *mainWindow, QWidget *parent) : QFrame(parent), ui(new Ui::FacePickFrame) {
    this->ui->setupUi(this);
    this->mainWindow = mainWindow;

    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
        QString nameInput = this->ui->lineEdit->text();
        QString sidInput = this->ui->lineEdit_2->text();
        if (nameInput == "" || sidInput == "") {
            QMessageBox::information(this, "Error", "姓名和学号不能为空");
            return;
        }
        student stu = {sidInput.toInt(), nameInput.toStdString(), 0};

    });
}

FacePickFrame::~FacePickFrame()
{
    this->camera->stop();
    this->camera->unload();
    this->mainWindow->show();
    delete ui;
}

void FacePickFrame::closeEvent(QCloseEvent *e) {
    this->camera->stop();
    this->camera->unload();
    this->mainWindow->show();
}

void FacePickFrame::showEvent(QShowEvent *e) {
    this->camera = new QCamera(QCameraInfo::defaultCamera());
    this->camera->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder);
    this->camera->setViewfinder(this->ui->widget_2);
    this->camera->start();
}
