// Header files for main test window

#ifndef MAINTESTWINDOW_H
#define MAINTESTWINDOW_H
#include <QWidget>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QDateTime>
#include <QDir>
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QApplication>
#include <Qpoint>
#include <QDesktopWidget>
#include <QTextStream>
#include <QFile>
#include <QTime>

//create maintestwindow class and declare classes being used
namespace Ui {
class maintestwindow;
}

// Define subclass
class QCamera;
class QCameraImageCapture;
class maintestwindow : public QWidget
{
    Q_OBJECT

public:
    explicit maintestwindow(QWidget *parent = 0);
    ~maintestwindow();

// create private slots (functions)
private slots:
    void newPoint();
    void enterScreenSize();
    void on_dot1_clicked();

    int randomNumber(int low, int high);

// Private ui object provides code for setting up user interface
private:
    Ui::maintestwindow *ui;
    QCamera *mCamera;
    QCameraImageCapture *mCameraImageCapture;
};

#endif // MAINTESTWINDOW_H
