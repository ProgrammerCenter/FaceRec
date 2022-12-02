#ifndef FACEPICKFRAME_H
#define FACEPICKFRAME_H

#include <QFrame>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <QShowEvent>
#include <QCameraInfo>
#include <QCamera>
#include <QVideoWidget>
#include <QCameraViewfinderSettings>
#include <QVideoProbe>

#include "database.h"
#include "traindialog.h"
#include "trainthread.h"

namespace Ui {
class FacePickFrame;
}

class FacePickFrame : public QFrame
{
    Q_OBJECT

public:
    explicit FacePickFrame(QWidget *mainWindow, QWidget *parent = nullptr);
    ~FacePickFrame();

private:
    Ui::FacePickFrame *ui;
    QWidget *mainWindow;
    QCamera *camera;
    TrainThread *trainThread;
    TrainDialog *trainDialog;
    QVideoProbe *probe;

private slots:
    void trainFinished();

protected:
    void closeEvent(QCloseEvent *e) override;
    void showEvent(QShowEvent *e) override;
};

#endif // FACEPICKFRAME_H
