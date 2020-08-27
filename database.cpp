#include "database.h"
#include "qdebug.h"

#include "QDateTime"
#include "QDirIterator"

DataBase::DataBase(QObject *parent) : QThread(parent)
{
}

void DataBase::run() {
    QString db_Name;
    db_Name.append("C:/Development/baseDeDatos1.sqlite");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_Name);

    if(db.open()) {
        qDebug() << "Se ha conectado a la BD";
        crearTabla();
        leerDatos();
    } else {
        qDebug() << "ERROR al crear la BD";
    }
}

void DataBase::crearTabla()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS imagenes( "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name VARCHAR(100)"");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()) {
        qDebug() << "Se ha creado la tabla o ya existe";
    } else {
        qDebug() << "La tabla no se ha podido crear" << crear.lastError();
    }
}

void DataBase::leerDatos()
{
    QDirIterator images_Repository(images, QDirIterator::Subdirectories);
    while(images_Repository.hasNext()) {
        images_Repository.next();
        QFileInfo images_Info(images_Repository.filePath());
        if((images_Info.fileName() == ".") || (images_Info.fileName() == "..") || (images_Info.fileName() == " ")){
        } else {
            if(images_Info.isFile() && images_Info.suffix() == "jpg"){
                ingresarDatos(images_Info.lastModified());
            }
        }
    }
}

void DataBase::ingresarDatos(QDateTime(file_Date))
{

    QString date = file_Date.toString("dd.MM.yyyy");
    QString consulta;
    consulta.append("INSERT INTO imagenes( "
                    "name)"
                    "VALUES("
                    " ' "+date+ " ' "
                                     "); ");
    QSqlQuery insertar;
    insertar.prepare(consulta);
    if(insertar.exec()) {
        qDebug() << "Se ha insertado la imagen a la tabla";
    } else {
        qDebug() << "No se ha podido insertar la imagen a la tabla" << insertar.lastError();
    }
}
