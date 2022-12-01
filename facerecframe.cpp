#include "facerecframe.h"
#include "ui_facerecframe.h"

FaceRecFrame::FaceRecFrame(QWidget *mainWindow, QWidget *parent) : QFrame(parent), ui(new Ui::FaceRecFrame) {
    this->ui->setupUi(this);
    this->mainWindow = mainWindow;
}

FaceRecFrame::~FaceRecFrame()
{
    this->camera->stop();
    this->camera->unload();
    delete ui;
}

void FaceRecFrame::closeEvent(QCloseEvent *e) {
    this->camera->stop();
    this->camera->unload();
    this->mainWindow->show();
}

void FaceRecFrame::showEvent(QShowEvent *e) {
    this->camera = new QCamera(QCameraInfo::defaultCamera());
    this->camera->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder);
    this->camera->setViewfinder(this->ui->widget_2);
    this->camera->start();
}
