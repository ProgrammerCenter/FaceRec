#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << access("haarcascade_frontalface_default.xml",  F_OK);
    qDebug() << access(this->modelPath.c_str(), F_OK);
    if (access("haarcascade_frontalface_default.xml",  F_OK) != 0) {
        throw std::runtime_error("Face detector model doesn't exists.");
    }
    this->detector = new CascadeClassifier();
    this->detector->load("haarcascade_frontalface_default.xml");
    if (access(this->modelPath.c_str(), F_OK) == 0) {
        struct stat statbuf;
        stat(this->modelPath.c_str(), &statbuf);
        if (statbuf.st_size > 100) {
                this->modelTrained = true;
        }
        this->recoginzer = LBPHFaceRecognizer::create();
        this->recoginzer->read(this->modelPath);
    } else {
        this->recoginzer = LBPHFaceRecognizer::create();
    }

    this->database = new Database();

    ui->setupUi(this);
    this->facePickFrame = new FacePickFrame(this, nullptr);
    this->faceRecFrame = new FaceRecFrame(this, nullptr);
    connect(this->ui->pushButton_3, &QPushButton::clicked, this, &QCoreApplication::quit);
    connect(this->ui->pushButton, &QPushButton::clicked, this, [this]() {
        this->hide();
        this->facePickFrame->show();
    });
    connect(this->ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        this->hide();
        this->faceRecFrame->show();
    });
}

Mat MainWindow::faceDetect(Mat inp) {
    vector<Rect> faceAreas;
    detector->detectMultiScale(inp, faceAreas);
    if (faceAreas.size() < 1) {
        return Mat();
    } else {
        Rect face = faceAreas.at(0);
        return inp(face);
    }
}

int MainWindow::recognize(Mat face, double &confidence) {
    if (!this->modelTrained) {
        return -1;
    }
    int sid;
    this->recoginzer->predict(face, sid, confidence);
    if (confidence > 0.8) {
        return -1;
    }
    return sid;
}

void MainWindow::trainModel(vector<Mat> faces, vector<int> ids) {
    if (this->modelTrained) {
        this->recoginzer->update(faces, ids);
    } else {
        this->recoginzer->train(faces, ids);
        this->modelTrained = true;
    }
}

MainWindow::~MainWindow()
{
    delete database;
    this->recoginzer->save(this->modelPath);
    delete recoginzer;
    delete detector;
    delete ui;
    delete facePickFrame;
    delete faceRecFrame;
}

