#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Database::getInstace();
    Recognizer::getInstance();
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

Recognizer *MainWindow::getRecognizer() {
    return this->recognizer;
}

Database *MainWindow::getDatabase() {
    return this->database;
}

MainWindow::~MainWindow()
{
    delete recognizer;
    delete database;
    delete ui;
    delete facePickFrame;
    delete faceRecFrame;
}

