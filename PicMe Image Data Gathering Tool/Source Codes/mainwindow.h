//Define libraries requires
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDateTime>
#include <QLineEdit>
#include <QCryptographicHash>
#include <QDebug>
#include "maintestwindow.h"

// Define namespace class
namespace Ui {
class MainWindow;
}

// Define subclass
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    maintestwindow *test;

private slots:
    void on_startButton_clicked(); // Create start button function

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

// Private ui object provides code for setting up user interface
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
