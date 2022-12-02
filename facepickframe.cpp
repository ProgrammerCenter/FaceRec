#include "facepickframe.h"
#include "ui_facepickframe.h"

FacePickFrame::FacePickFrame(QWidget *mainWindow, QWidget *parent) : QFrame(parent), ui(new Ui::FacePickFrame) {
    this->ui->setupUi(this);
    this->mainWindow = mainWindow;
    this->trainDialog = new TrainDialog(this);
    this->probe = new QVideoProbe(this);
    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
        QString nameInput = this->ui->lineEdit->text();
        QString sidInput = this->ui->lineEdit_2->text();
        if (nameInput == "" || sidInput == "") {
            QMessageBox::information(this, "Error", "姓名和学号不能为空");
            return;
        }
        this->trainThread = new TrainThread(Recognizer::getInstance(), this->ui->lineEdit_2->text().toInt(), this);
        connect(trainThread, &TrainThread::finished, this, &FacePickFrame::trainFinished, Qt::QueuedConnection);
        connect(trainThread, &TrainThread::changeProgress, trainDialog, &TrainDialog::changeProgress, Qt::QueuedConnection);
        connect(trainThread, &TrainThread::changeState, trainDialog, &TrainDialog::changeState, Qt::QueuedConnection);
        connect(this->probe, &QVideoProbe::videoFrameProbed, trainThread, &TrainThread::onProbeFrameSlot);
        this->trainDialog->show();
        this->trainThread->start();
    });
}

FacePickFrame::~FacePickFrame()
{
    this->camera->stop();
    this->camera->unload();
    this->mainWindow->show();
    if (this->trainThread != nullptr) {
        delete this->trainThread;
    }
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
    this->probe->setSource(this->camera);
}

void FacePickFrame::trainFinished() {
    disconnect(this->probe, &QVideoProbe::videoFrameProbed, this->trainThread, &TrainThread::onProbeFrameSlot);
    delete this->trainThread;
    this->trainDialog->hide();
    QString nameInput = this->ui->lineEdit->text();
    QString sidInput = this->ui->lineEdit_2->text();
    student stu = {sidInput.toInt(), nameInput.toStdString(), 0};
    Database::getInstace()->newStudent(stu);
    QMessageBox::information(this, "Success", "添加完成");
    this->ui->lineEdit->setText("");
    this->ui->lineEdit_2->setText("");
}
