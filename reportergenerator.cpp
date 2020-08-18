#include "reportergenerator.h"

#include "QDebug"
#include "QDirIterator"
#include "QPdfWriter"
#include "QPaintEngineState"
#include "QStylePainter"
#include <QtPrintSupport/QPrintEngine>
#include "QFileDialog"

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
            }
        }
    }
}
