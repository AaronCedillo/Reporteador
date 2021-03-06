#include "reporter.h"
#include "ui_reporter.h"
#include "reportergenerator.h"
#include "database.h"

#include "QFileDialog"
#include "QDebug"
#include "QDir"
#include "QMessageBox"
#include "QDateTime"
#include "QDesktopServices"
#include "QFile"

QString ImagesFolder;
QDate date;

Reporter::Reporter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Reporter)
{
    ui->setupUi(this);
    reporter_Folder();

    mDataBase = new DataBase(this);
    mReporter = new reporterGenerator(this);

    connect(mReporter, &reporterGenerator::Images, [&] (QString ImagesPath){
        //qDebug() << ImagesPath;
    });

    date = QDate::currentDate();
    ui -> startDate -> setDate(date);
    ui -> finalDate -> setDate(date);
}

Reporter::~Reporter()
{
    delete ui;
}

void Reporter::on_selectFolder_clicked()
{
    ImagesFolder = QFileDialog::getExistingDirectory(this,
                                                     tr("Select Folder"),
                                                     "/home", QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);

    ui -> folderPath -> setText(ImagesFolder);
}

void Reporter::on_reportGenerator_clicked()
{
    if(ui -> folderPath->text().isEmpty()){
        QMessageBox::information(this, tr("WARNING"), ("Seleccione un folder"));
    } else {
        reporter_Folder();
        QString name = "Reporte (" + date.toString("dd.MM.yyyy") + ")";
        QString fileName = "C:/Reportes/" + name;
        QFile reporter(fileName + ".pdf");
        if(reporter.open(QIODevice::WriteOnly | QIODevice::Text)) {
            reporter.close();
            QMessageBox::information(this, tr("Mensaje"), ("Documento guardado correctamente"));
        } else {
            QMessageBox::critical(this, tr("Warning"), reporter.errorString());
        }

        int startDate_Day = ui ->startDate -> date().day();
        int startDate_Month = ui -> startDate -> date().month();
        int finalDate_Day = ui -> finalDate -> date().day();
        int finalDate_Month = ui -> finalDate -> date().month();

        mReporter -> startDay_Reporter = startDate_Day;
        mReporter -> finalDay_Reporter = finalDate_Day;
        mReporter -> startMonth_Reporter = startDate_Month;
        mReporter -> finalMonth_Reporter = finalDate_Month;
        mReporter -> pdf_File = fileName;
        mReporter -> folder_Images = ImagesFolder;
        mDataBase -> start(QThread::HighestPriority);

        mDataBase -> images = ImagesFolder;
        mReporter -> start(QThread::HighestPriority);
    }
}

void Reporter::reporter_Folder(){
    if(QDir("C:/Reportes").exists()){
    } else{
        QDir().mkdir("C:/Reportes");
    }
}
