#include "recognizer.h"

Recognizer::Recognizer()
{
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
}

Mat Recognizer::faceDetect(Mat inp) {
    vector<Rect> faceAreas;
    detector->detectMultiScale(inp, faceAreas);
    if (faceAreas.size() < 1) {
        return Mat();
    } else {
        Rect face = faceAreas.at(0);
        return inp(face);
    }
}

int Recognizer::recognize(Mat face, double &confidence) {
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

void Recognizer::trainModel(vector<Mat> faces, vector<int> ids) {
    if (this->modelTrained) {
        this->recoginzer->update(faces, ids);
    } else {
        this->recoginzer->train(faces, ids);
        this->modelTrained = true;
    }
}

Recognizer::~Recognizer () {
    this->recoginzer->save(this->modelPath);
    delete recoginzer;
    delete detector;
}

Recognizer *Recognizer::getInstance() {
    if (Recognizer::instance == nullptr) {
        Recognizer::instance = new Recognizer();
    }
    return Recognizer::instance;
}
