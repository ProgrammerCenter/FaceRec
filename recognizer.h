#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

#include <unistd.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;
using namespace cv::face;

class Recognizer
{
public:
    ~Recognizer();
    Mat faceDetect(Mat inp);
    int recognize(Mat face, double &confidence);
    void trainModel(vector<Mat> faces, vector<int> ids);
    static Recognizer *getInstance();

private:
    Recognizer();

    static Recognizer *instance;
    string modelPath = "model.yml";
    FaceRecognizer *recoginzer;
    CascadeClassifier *detector;
    bool modelTrained = false;

};

#endif // RECOGNIZER_H
