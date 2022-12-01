#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QThread>
#include <QVideoFrame>

#include <opencv2/opencv.hpp>

#include "mainwindow.h"

#define SAMPLES 100

using namespace std;

class TrainThread : public QThread
{
    Q_OBJECT
public:
    TrainThread(MainWindow *mainWindow, int sid, QWidget *parent = nullptr);
    ~TrainThread();
private:
    MainWindow *mainWindow;
    int sid;
    vector<Mat> faces;
    vector<int> labels;
    int sampleCollected = 0;

    void run() override;

public slots:
    void onProbeFrameSlot(const QVideoFrame &frame);

signals:
    void changeProgress(int p);
    void changeState(QString state);
    void finished();
};

#endif // TRAINTHREAD_H
