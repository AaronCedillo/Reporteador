#ifndef REPORTER_H
#define REPORTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Reporter; }
QT_END_NAMESPACE

class reporterGenerator;
class DataBase;

class Reporter : public QMainWindow
{
    Q_OBJECT

public:
    Reporter(QWidget *parent = nullptr);
    ~Reporter();

private slots:
    void on_selectFolder_clicked();
    void on_reportGenerator_clicked();
    void reporter_Folder();

private:
    Ui::Reporter *ui;
    reporterGenerator *mReporter;
    DataBase *mDataBase;
};
#endif // REPORTER_H
