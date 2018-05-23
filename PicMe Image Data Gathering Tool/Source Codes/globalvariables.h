// Defines the global variables being used in the project

#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <qtglobal> //Include QT global variable library
#include <QDir>
#include <QString>

QT_BEGIN_NAMESPACE  //Define substitution "QString"
class QString;
QT_END_NAMESPACE

// Define classes, public functions and ecternal variables
class globalvariables
{
public:
    globalvariables();
};

extern QString timeStamp;
extern QByteArray uniqueID;
extern QString directory;
extern int wearGlasses;

#endif // GLOBALVARIABLES_H
