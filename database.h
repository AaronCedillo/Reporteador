#ifndef DATABASE_H
#define DATABASE_H

#include <QThread>
#include "QtSql/qsqldatabase.h"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"

class DataBase : public QThread
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    QString images;

signals:

protected:
    void run();
    void crearTabla();
    void leerDatos();
    void ingresarDatos(QString fileNames);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
