#ifndef FACERECFRAME_H
#define FACERECFRAME_H

#include <QFrame>
#include <QCloseEvent>
#include <QShowEvent>
#include <QCameraInfo>
#include <QCamera>
#include <QVideoWidget>
#include <QCameraViewfinderSettings>

namespace Ui {
class FaceRecFrame;
}

class FaceRecFrame : public QFrame
{
    Q_OBJECT

public:
    explicit FaceRecFrame(QWidget *mainWindow, QWidget *parent = nullptr);
    ~FaceRecFrame();

protected:
    void closeEvent(QCloseEvent *e) override;
    void showEvent(QShowEvent *e) override;

private:
    Ui::FaceRecFrame *ui;
    QWidget *mainWindow;
    QCamera *camera;
};

#endif // FACERECFRAME_H
