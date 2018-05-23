// Include necessary header files
#include "maintestwindow.h"
#include "ui_maintestwindow.h"
#include "globalvariables.h"
#include "mainwindow.h"

// Create variables
int pointNo = 0; // Point number is for the state machine below for circle position in test
int imageNum = 1; // Create an integer for use for automatic naming of images taken
int height = 0; // Create height variable
int width = 0; // Create width variable
int i = 0;

Q_DECLARE_METATYPE(QCameraInfo) // QCameraInfo is a class whos data type not supported by QVariant,
                                // so it needs to be declared as a metatype as shown.

// Create instance of the main window
maintestwindow::maintestwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::maintestwindow)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(enterScreenSize())); // Timer class which has its own functions
                                                            // Single shot happens once after 200ms and doesnt happen again
                                                            // When it appens it runs enter screen size function
    int height1 = QApplication::desktop()->height(); // Grab desktop height from QApplication class
    int width1 = QApplication::desktop()->width();   // Grab desktop width from QApplication class
    int halfWidth = width1/2;
    int halfHeight = height1/2;
    ui->label->setGeometry(halfWidth-10,halfHeight-10,20,20);
    ui->dot1->setGeometry(halfWidth-3,halfHeight-3,6,6);
    QTimer::singleShot(200, this, SLOT(timeStamp = QDateTime::currentDateTime().toString("dd_MMM_yyyy_HH_mm_ss");));
    // Current timestamp will be used as folder name for data set from each test
    mCamera = new QCamera(this); // variable mCamera is new camera instance
    mCameraImageCapture = new QCameraImageCapture(mCamera, this); // variable mCameraImageCapture is an instance to capture an image.
    mCamera->start(); // Start camera by calling start function inside mCamera
    mCamera->searchAndLock(); // Locks in default camera settings
    // Create seed for the random number function
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

// If maintestwindow ui isnt open
maintestwindow::~maintestwindow()
{
    delete ui; // delete ui
    delete mCameraImageCapture; // delete image capture
    delete mCamera; // delete mCamera
}

// enterScreenSize function
void maintestwindow::enterScreenSize()
{
    int height = QApplication::desktop()->height(); // Grab desktop height from QApplication class
    int width = QApplication::desktop()->width();   // Grab desktop width from QApplication class
    QString filename="Settings.txt"; // Creating string variable called filename and inputting "settings.txt" as name
    QFile file1(filename); // Creates file instance
    if (file1.open(QIODevice::WriteOnly|QIODevice::Text)) // If the created file opens
    {
            QTextStream out(&file1); // Out is instance of the Qtxtstream class.
            out << "Screen Dimensions..." << endl; // Print to txt file
            out << "Height: " << height << endl;
            out << "Width: " << width << endl;
    }
}

// Generate randowm number function
int maintestwindow::randomNumber(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

// Create new target location
void maintestwindow::newPoint()
{
    int height = QApplication::desktop()->height(); // Saves desktop height
    int width = QApplication::desktop()->width();   // Saves desktop width
    if(pointNo == 0) // State machine: if point is 0:
    {
      ui->label->setGeometry(10,10,20,20);// Set button coordinates and size (x,y,h,w)
      ui->dot1->setGeometry(17,17,6,6);   // Set button coordinates and size (x,y,h,w)
      pointNo = 1; // Change pointNo to 1
    }
    else if(pointNo ==1) // If pointno = 1
    {
        ui->label->setGeometry(width-30,10,20,20);
        ui->dot1->setGeometry(width-23,17,6,6); // Set button coordinates and size (x,y,h,w)
        pointNo = 2; // Change pointno to 2
    }
    else if(pointNo ==2) // If pointno is 2 :
    {
        ui->label->setGeometry(10,height-30,20,20);
        ui->dot1->setGeometry(17,height-23,6,6); // Set button coordinates and size (x,y,h,w)
        pointNo = 3; // Change pointno to 3.
    }
    else if(pointNo ==3) // If pointno = 3
    {
        ui->label->setGeometry(width-30,height-30,20,20);
        ui->dot1->setGeometry(width-23,height-23,6,6);
        pointNo = 4; // Change pointno to 0
    }
    else if(pointNo == 4 && i < 100) // If the number of targets in the test so far is less than 100
    {
        int x1 = randomNumber(10, width-30);
        int y1 = randomNumber(10, height-30);
        ui->label->setGeometry(x1,y1,20,20);
        ui->dot1->setGeometry(x1+7,y1+7,6,6);
        i++; // Increment target number
    }
    else
    {
        close(); // Close application after 104 targets have appeared on screen and been clicked
    }
}

// funtion for mouse click event on a target
void maintestwindow::on_dot1_clicked()
{
    int height = QApplication::desktop()->height(); // Grab desktop height from QApplication class
    int width = QApplication::desktop()->width();   // Grab desktop width from QApplication class
    QPoint xyCoords = ui->dot1->cursor().pos();     // Screen coordinates
    QString path = QDir::currentPath(); // Gets the current path to the directory(folder) from which the program is running
    path += directory; // Add test folder to the current path
    path += "/";
    QDir mDir(directory);
    mDir.mkpath(timeStamp);
    path += timeStamp;
    QString filename = path; // Creates filename string named after the current path
    filename += "/";         // Add / to the end of filename to show entry to a new directory
    QString imgNum = QString::number(imageNum,10); // Create string to change int to string
    filename += "/image"; // Add /image to filename
    filename += imgNum;   // Add imgNo value to filename so that each picture saved has its own name
    QString ImageData = filename;
    filename += ".jpg";   // Add .jpg to filename to create the full path name being used. The path is built up piece by piece with the last few lines of code. i.e. end result = G:\Team Drives\Project Software\Eye\Eye\build-EyeTest-Desktop_Qt_5_10_0_MinGW_32bit-Debug\TestResults etc. depending on where its running from
    ImageData += ".txt";  // Same process as above but for text file for each image
    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile); // Captures image to a file instead of buffer
    QImageEncoderSettings imageEncoderSettings;  // New instance of image encoder settings class.
    imageEncoderSettings.setCodec("image/jpeg"); // Sets image to save as a jpeg.
    imageEncoderSettings.setResolution(1600, 1200); // Resolution of the image.
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings); // Input settings into the instance
    mCamera->setCaptureMode(QCamera::CaptureStillImage); // Changing mode to capture a still image
    mCameraImageCapture->capture(filename); // Image capture occurs here, save it as the file picked at the start
    imageNum ++; // Increment image number
    QFile file1(ImageData); // Creates file instance
    if (file1.open(QIODevice::WriteOnly|QIODevice::Text)) // If the created file opens
    {
            QTextStream out(&file1); // Out is instance of the Qtxtstream class.
            out << "Screen Dimensions:" << endl; // Print to txt file
            out << "Height: " << height << endl; // Print to txt file
            out << "Width: " << width << endl;
            out << "X Coordinate:" << xyCoords.x() << endl;
            out << "Y Coordinate:" << xyCoords.y() << endl;

            // Prints other information to the text file such as if user wears glasses etc.
            if(wearGlasses == 1)
            {
                out << "User wears glasses: YES" << endl;
            }
            else
            {
                out << "User wears glasses: NO" << endl;
            }

            if(xyCoords.x() < 683 & xyCoords.y() < 384)
            {
                out << "Quadrant:1" << endl;
            }

            else if(xyCoords.x() < 683 & xyCoords.y() > 384)
            {
                out << "Quadrant:3" << endl;
            }

            else if(xyCoords.x() > 683 & xyCoords.y() < 384)
            {
                out << "Quadrant:2" << endl;
            }

            else if(xyCoords.x() > 683 & xyCoords.y() > 384)
            {
                out << "Quadrant:4" << endl;
            }
            else
            {
                out << "Quadrant:Centre" << endl;
            }

    }
    newPoint(); // Call new point function
}
