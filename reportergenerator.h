#ifndef REPORTERGENERATOR_H
#define REPORTERGENERATOR_H

#include <QThread>

class reporterGenerator : public QThread
{
    Q_OBJECT
public:
    explicit reporterGenerator(QObject *parent = nullptr);
    QString folder_Images; //Esto sera igualmente una DB
    QString pdf_File;
    int startDay_Reporter;
    int finalDay_Reporter;
    int startMonth_Reporter;
    int finalMonth_Reporter;

signals:
    void Images(QString);

protected:
    void run();

};

#endif // REPORTERGENERATOR_H
