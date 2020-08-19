#include "reportergenerator.h"

#include "QDebug"
#include "QDirIterator"
#include "QPdfWriter"
#include "QPaintEngineState"
#include "QStylePainter"
#include <QtPrintSupport/QPrintEngine>
#include "QFileDialog"
#include "QDateTime"

reporterGenerator::reporterGenerator(QObject *parent) :
    QThread(parent)
{
}

void reporterGenerator::run(){   

    QDirIterator images_Directory(folder_Images, QDirIterator::Subdirectories);
    while(images_Directory.hasNext()) {
        images_Directory.next();
        QFileInfo images_Files(images_Directory.filePath());
        if((images_Files.fileName() == ".") || (images_Files.fileName() == "..") || (images_Files.fileName() == " ")){
        } else {
            if(images_Files.isFile() && images_Files.suffix() == "jpg"){
                QDateTime data_Files = images_Files.lastModified();
                int startDay_File = data_Files.date().day();
                int startMonth_File = data_Files.date().month();
                if(startDay_File >= startDay_Reporter && startDay_File <= finalDay_Reporter){
                    if(startMonth_File >= startMonth_Reporter && startMonth_File <= finalMonth_Reporter){
                        emit Images(images_Files.fileName());
                    }
                }
            }
        }
    }
}
