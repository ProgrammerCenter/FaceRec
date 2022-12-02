#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

#include "facepickframe.h"
#include "facerecframe.h"
#include "database.h"
#include "recognizer.h"

#include <sys/stat.h>
#include <unistd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
using namespace cv;
using namespace cv::face;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Recognizer *getRecognizer();
    Database *getDatabase();

private:
    FacePickFrame *facePickFrame;
    FaceRecFrame *faceRecFrame;
    Ui::MainWindow *ui;
    Database *database;
    Recognizer *recognizer;

};
#endif // MAINWINDOW_H
