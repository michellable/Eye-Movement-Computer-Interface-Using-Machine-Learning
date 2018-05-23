// This software was used in conjunction with batch files
// to segregate copies of the original images collected during testing into folders
// named after the different quadrants on the screen.
// Quad 1 = top left, Quad 2 = top right, Quad 3 = bottom left, Quad 4 = bottom right
// A sequence file was created in each of the folders which the images were being copied into
// in order to keep track of the images being copied in and to number them in sequence as they entered.

// Include necessary libraries
#include <QCoreApplication>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Declare variables
QString quadrant;
char* quadNo;

// Main program
int main()
{
    // int i is used for counting up through images in each test subjects results folder
    // There was approximately 110 photos in each subjects folder
    int i = 0;
    while(i < 110)
    {
        QString fileNo = QString::number(i,10); // Change integer to string
        QString txtFileName = "image"; // Construct image name for copied image
        txtFileName += fileNo;
        QString imageFileName = txtFileName;
        txtFileName += ".txt"; // Construct text file name for text file
        imageFileName += ".jpg";
        QFile openTxtFile(txtFileName); // read from input file stream "txtFileName"
        if(!openTxtFile.exists()) // If there is no text file available for an associated image
        {
            qDebug() << "text file doesnt exist"<< txtFileName; // Print to console
        }
        else
        {
            qDebug() << txtFileName <<"text file found"; // Print to console
        }

        if(openTxtFile.open(QIODevice::ReadOnly|QIODevice::Text)) // Open text file as read only
        {
            qDebug() << "text file opened:" << txtFileName;
            QTextStream stream(&openTxtFile);
            int l = 1; // Create integer for line number in text file
            while (!stream.atEnd()) // While line number is less than 8
            {
                QString line = stream.readLine();
                qDebug() << "current line number:" << l;
                qDebug() << "read line="<< line;

                if (l == 7) // look for line 7
                {
                    quadrant = line; // Puts the value of line 7 as quadrant
                    qDebug() << "line 7 =" << quadrant;
                    QByteArray x = quadrant.toLatin1();
                    char* quadTok = x.data(); // Create character quadTok and setting it as the length of line 7 and adding 1
                    char* tok; // Create another character array called tok
                    tok = strtok(quadTok, ":"); // Set the delimeter for tokenising the line

                    while (tok != NULL) // while token is not empty
                    {
                        if (tok != "Quadrant") // if the value of the token is not Quadrant
                        {
                            quadNo = tok; // make tok equal to the value that is not Quadrant i.e. the quadrant number
                            qDebug() << "Quadrant number = " << quadNo;
                        }
                        tok = strtok(NULL, ":"); // reset the token by making it null
                    }
                    int quadInteger = atoi(quadNo); // Change quadrant number to an integer

                    if (quadInteger == 1) // If quadrant is quadrant 1
                    {
                        qDebug() << "image is in quad 1";
                        unsigned int fileSeq; //creating integer flag for file sequence
                        QString y = "../../../../test/Quadrant_1/sequenceFile.txt";
                        qDebug() << y;
                        QFile openSeqFile(y); // Open the sequence file in the folder
                        if(!openSeqFile.exists())
                        {
                            qDebug() << "Seq File doesnt exist"<< txtFileName;
                        }
                        else
                        {
                            qDebug() << txtFileName << " Seq file found";
                        }

                        if(openSeqFile.open(QIODevice::ReadOnly|QIODevice::Text)) // Open the sequence file as read only
                        {
                            QTextStream seqStream(&openSeqFile);
                            qDebug() << "sequence file opened";
                            while (!seqStream.atEnd())
                            {
                                QString line1 = seqStream.readLine(); //  read the value on line 1 of the sequence file
                                qDebug() << "seq file value is:" << line1;
                                fileSeq = line1.toInt(); // Change the sequence file value to an int
                                fileSeq ++; // Increment sequence file
                                QString fileName = "image" + line1 + ".jpg"; // create string for file name = image + file seq no. + .jpg
                                QString filePath = "../../../../test/Quadrant_1/";
                                filePath += fileName;
                                QFile::copy(imageFileName, filePath); // Copy the image to the filepath specified
                                QString newSeq = QString::number(fileSeq,10); // Create variable for updated sequence number
                                openSeqFile.close(); // Close the sequence file
                                if(openSeqFile.open(QIODevice::WriteOnly|QIODevice::Text)) // Reopen the sequence file
                                {
                                    QTextStream seqStream(&openSeqFile);
                                    seqStream << newSeq; // Update the sequence file number
                                    openSeqFile.close(); // Close the sequence file
                                }
                            }
                        }
                    }

                    else if (quadInteger == 2) // As above
                    {
                        qDebug() << "image is in Quad 2";
                        unsigned int fileSeq; //creating integer flag for file sequence
                        QString y = "../../../../test/Quadrant_2/sequenceFile.txt";
                        qDebug() << "directory =" << y;
                        QFile openSeqFile(y);

                        if(!openSeqFile.exists())
                        {
                            qDebug() << "Seq file doesnt exist"<< txtFileName;
                        }
                        else
                        {
                            qDebug() << txtFileName <<"seq file found";
                        }

                        if(openSeqFile.open(QIODevice::ReadOnly|QIODevice::Text))
                        {
                            QTextStream seqStream(&openSeqFile);
                            qDebug() << "sequence file opened";
                            while (!seqStream.atEnd()) // while line number is less than 8
                            {
                                QString line1 = seqStream.readLine();
                                qDebug() << "seq file value is:" << line1;
                                fileSeq = line1.toInt();
                                fileSeq ++;
                                //qDebug() << fileSeq;
                                QString fileName = "image" + line1 + ".jpg"; // create string for file name = image + file seq no. + .jpg
                                QString filePath = "../../../../test/Quadrant_2/";
                                filePath += fileName;
                                //QFile imgFile(imageFileName);
                                QFile::copy(imageFileName, filePath);
                                QString newSeq = QString::number(fileSeq,10);
                                openSeqFile.close();
                                if(openSeqFile.open(QIODevice::WriteOnly|QIODevice::Text))
                                {
                                    QTextStream seqStream(&openSeqFile);
                                    seqStream << newSeq;
                                    openSeqFile.close();
                                }
                            }
                        }
                    }

                    else if (quadInteger == 3) // As above
                    {
                        qDebug() << "image is in quad 3";
                        unsigned int fileSeq; //creating integer flag for file sequence
                        QString y = "../../../../test/Quadrant_3/sequenceFile.txt";
                        qDebug() << y;
                        QFile openSeqFile(y);
                        if(!openSeqFile.exists())
                        {
                            qDebug() << "Seq File doesnt exist"<< txtFileName;
                        }
                        else
                        {
                            qDebug() << txtFileName << " Seq file found";
                        }

                        if(openSeqFile.open(QIODevice::ReadOnly|QIODevice::Text))
                        {
                            QTextStream seqStream(&openSeqFile);
                            qDebug() << "sequence file opened";
                            while (!seqStream.atEnd()) // while line number is less than 8
                            {
                                QString line1 = seqStream.readLine();
                                qDebug() << "seq file value is:" << line1;
                                fileSeq = line1.toInt();
                                fileSeq ++;
                                //qDebug() << fileSeq;
                                QString fileName = "image" + line1 + ".jpg"; // create string for file name = image + file seq no. + .jpg
                                QString filePath = "../../../../test/Quadrant_3/";
                                filePath += fileName;
                                //QFile imgFile(imageFileName);
                                QFile::copy(imageFileName, filePath);
                                QString newSeq = QString::number(fileSeq,10);
                                openSeqFile.close();
                                if(openSeqFile.open(QIODevice::WriteOnly|QIODevice::Text))
                                {
                                    QTextStream seqStream(&openSeqFile);
                                    seqStream << newSeq;
                                    openSeqFile.close();
                                }
                            }
                        }
                    }

                    else if (quadInteger == 4) // As above
                    {
                        qDebug() << "image is in quad 4";
                        unsigned int fileSeq; //creating integer flag for file sequence
                        QString y = "../../../../test/Quadrant_4/sequenceFile.txt";
                        qDebug() << y;
                        QFile openSeqFile(y);
                        if(!openSeqFile.exists())
                        {
                            qDebug() << "Seq File doesnt exist"<< txtFileName;
                        }
                        else
                        {
                            qDebug() << txtFileName << " Seq file found";
                        }

                        if(openSeqFile.open(QIODevice::ReadOnly|QIODevice::Text))
                        {
                            QTextStream seqStream(&openSeqFile);
                            qDebug() << "sequence file opened";
                            while (!seqStream.atEnd()) // while line number is less than 8
                            {
                                QString line1 = seqStream.readLine();
                                qDebug() << "seq file value is:" << line1;
                                fileSeq = line1.toInt();
                                fileSeq ++;
                                //qDebug() << fileSeq;
                                QString fileName = "image" + line1 + ".jpg"; // create string for file name = image + file seq no. + .jpg
                                QString filePath = "../../../../test/Quadrant_4/";
                                filePath += fileName;
                                //QFile imgFile(imageFileName);
                                QFile::copy(imageFileName, filePath);
                                QString newSeq = QString::number(fileSeq,10);
                                openSeqFile.close();
                                if(openSeqFile.open(QIODevice::WriteOnly|QIODevice::Text))
                                {
                                    QTextStream seqStream(&openSeqFile);
                                    seqStream << newSeq;
                                    openSeqFile.close();
                                }
                            }
                        }
                    }

                    else
                    {
                        qDebug() << "image is in the centre/Quad 0";
                        unsigned int fileSeq; //creating integer flag for file sequence
                        QString y = "../../../../test/Quadrant_0/sequenceFile.txt";
                        qDebug() << y;
                        QFile openSeqFile(y);
                        if(!openSeqFile.exists())
                        {
                            qDebug() << "Seq File doesnt exist"<< txtFileName;
                        }
                        else
                        {
                            qDebug() << txtFileName << " Seq file found";
                        }

                        if(openSeqFile.open(QIODevice::ReadOnly|QIODevice::Text))
                        {
                            QTextStream seqStream(&openSeqFile);
                            qDebug() << "sequence file opened";
                            while (!seqStream.atEnd()) // while line number is less than 8
                            {
                                QString line1 = seqStream.readLine();
                                qDebug() << "seq file value is:" << line1;
                                fileSeq = line1.toInt();
                                fileSeq ++;
                                //qDebug() << fileSeq;
                                QString fileName = "image" + line1 + ".jpg"; // create string for file name = image + file seq no. + .jpg
                                QString filePath = "../../../../test/Quadrant_0/";
                                filePath += fileName;
                                //QFile imgFile(imageFileName);
                                QFile::copy(imageFileName, filePath);
                                QString newSeq = QString::number(fileSeq,10);
                                openSeqFile.close();
                                if(openSeqFile.open(QIODevice::WriteOnly|QIODevice::Text))
                                {
                                    QTextStream seqStream(&openSeqFile);
                                    seqStream << newSeq;
                                    openSeqFile.close();
                                }
                            }
                        }
                    }
                }
                qDebug() << "l value =" << l;
                l++; // increment line number
            }
        }

        i++;
    }
    return 0;
}
