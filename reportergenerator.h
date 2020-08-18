#ifndef REPORTERGENERATOR_H
#define REPORTERGENERATOR_H

#include <QThread>

class reporterGenerator : public QThread
{
    Q_OBJECT
public:
    explicit reporterGenerator(QObject *parent = nullptr);
    QString folder_Images; //Esto sera igualmente una DB

signals:
    void Images(QString);

protected:
    void run();

};

#endif // REPORTERGENERATOR_H
