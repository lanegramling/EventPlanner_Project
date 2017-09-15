#ifndef ADDINGMODE_H
#define ADDINGMODE_H
#include <QMainWindow>
#include "session.h"
#include "event.h"
#include <list>
namespace Ui{
class AddingMode;
}
class AddingMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddingMode(Session *session, QWidget *parent = 0);
    ~AddingMode();
private:
    Ui::AddingMode *ui;

    QString person_name;   // adding data

    //searching data

    int EventIndex;
    QString EventName;
    int month;
    int year;
    int day;
    Session *session;
private slots:
    void receiveshow();
    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_3_clicked();


    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_listWidget_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

signals:
    void showEventPlanner();
};
#endif // ADDINGMODE_H
