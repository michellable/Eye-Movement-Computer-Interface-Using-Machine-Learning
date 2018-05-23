#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalvariables.h"
#include "maintestwindow.h"

int over18 = 0;
int wearGlasses = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked() //If start button is clicked open the test interface window
{
    timeStamp = QDateTime::currentDateTime().toString("dd_MMM_yyyy_HH_mm_ss");
    QString emailAdd = ui->userEmail->text();

    if(emailAdd == "")
    {
        ui->userEmail->setPlaceholderText("Please enter email address to continue");
    }
    else
    {
        if(over18 == 1)
        {
             directory = "./TestResults";
             QDir mDir(directory);
             emailAdd += "/*Add salt key here for security*/";
             uniqueID = QCryptographicHash::hash(emailAdd.trimmed().toLocal8Bit(), QCryptographicHash::Sha3_224);
             uniqueID = uniqueID.toHex();
             mDir.mkpath(uniqueID);
             directory += "/";
             directory += uniqueID;
             //qDebug() << uniqueID;
             //ui->userEmail->setText(uniqueID.toHex());
             test = new maintestwindow;  // Create the new test window
             test->showFullScreen(); // Open window in full screen
             close(); // Close current window (MainWindow)
        }
    }
}

void MainWindow::on_checkBox_toggled(bool checked) // Check box ensured users were over 18
{
    if(checked)
    {
        over18 = 1;
    }
    else
    {
        over18 = 0;
    }
}

void MainWindow::on_checkBox_2_toggled(bool checked) // Glasses checkbox sets variable for glasses
{
    if(checked)
    {
        wearGlasses = 1; // User is wearing glasses
    }
    else
    {
        wearGlasses = 0; // User isnt wearing glasses
    }
}
