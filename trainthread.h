#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVideoFrame>

#include <opencv2/opencv.hpp>
#include "recognizer.h"

#define SAMPLES 100

using namespace std;

class TrainThread : public QThread
{
    Q_OBJECT
public:
    TrainThread(Recognizer *recognizer, int sid, QObject *parent = nullptr);
    ~TrainThread();
private:
    Recognizer *recognizer;
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
