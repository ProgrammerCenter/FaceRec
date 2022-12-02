#include "trainthread.h"

TrainThread::TrainThread(Recognizer *recognizer, int sid, QObject *parent) : QThread(parent)
{
    this->sid = sid;
    this->recognizer = recognizer;
}

void TrainThread::run() {
    emit changeState("正在采集照片...");
    emit changeProgress(0);
    while (this->sampleCollected < SAMPLES)
        ;
    emit changeState("训练模型中...");
    recognizer->trainModel(this->faces, this->labels);
    emit finished();
}

void TrainThread::onProbeFrameSlot(const QVideoFrame &frame) {
    if (this->sampleCollected > SAMPLES) {
        return;
    }
    QVideoFrame cloneFrame(frame);
    int w = cloneFrame.width();
    int h = cloneFrame.height();

    if (cloneFrame.map(QAbstractVideoBuffer::ReadOnly) == false){
        qDebug()<<"map error";
        return ;
    }

    Mat grayImg;
    Mat matTemp = Mat(h, w, CV_8UC2, cloneFrame.bits(), static_cast<size_t>(cloneFrame.bytesPerLine()));
    cvtColor(matTemp, matTemp, COLOR_YUV2RGB_YUYV);
    cvtColor(matTemp, grayImg, COLOR_BGR2GRAY);
    Mat face = this->recognizer->faceDetect(grayImg);
    if (face.empty()) {
        face.release();
        grayImg.release();
        matTemp.release();
        cloneFrame.unmap();
        return;
    }
    this->faces.push_back(face);
    this->labels.push_back(this->sid);
    grayImg.release();
    matTemp.release();
    cloneFrame.unmap();
    emit changeProgress(this->sampleCollected > 100 ? 100 : this->sampleCollected);
}

TrainThread::~TrainThread() {
    for (Mat face : this->faces) {
        face.release();
    }
}
