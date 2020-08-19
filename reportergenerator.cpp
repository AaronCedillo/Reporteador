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
                emit Images(images_Files.fileName());
                QDateTime data_Files = images_Files.lastModified();
                QString data_StringFiles = data_Files.toString("dd.MM.yyyy");
                if(data_StringFiles == startDate_Reporter){
                    qDebug() << data_StringFiles;
                }
            }
        }
    }
}
