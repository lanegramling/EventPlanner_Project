#ifndef EVENTADMINMODE_H
#define EVENTADMINMODE_H
#include <QMainWindow>
#include <QDebug>
#include "session.h"
namespace Ui {
class EventAdminMode;
}
class EventAdminMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit EventAdminMode(Session *session, QWidget *parent = 0);
    ~EventAdminMode();


    QString Info_Collect(QString &EventName,QString &person_name, int month, int day, int year, int* time);
    // use to make all Information to a string, used for "Make Sure"

    void setStyle_calendarWidget();
private:
    Ui::EventAdminMode *ui;

    //member variable: use to store the temp information from user
    int months; // month
    int days;   // day
    QString EventName; // Event Name
    QString person_name; //Event creater name
    int* times;

    Session *session;

private slots:
    void receiveshow();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_lineEdit_textEdited(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_checkBox_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_4_clicked(bool checked);
    void on_checkBox_5_clicked(bool checked);
    void on_checkBox_6_clicked(bool checked);
    void on_checkBox_7_clicked(bool checked);
    void on_checkBox_8_clicked(bool checked);
    void on_checkBox_9_clicked(bool checked);
    void on_checkBox_10_clicked(bool checked);
    void on_checkBox_11_clicked(bool checked);
    void on_checkBox_12_clicked(bool checked);
    void on_checkBox_13_clicked(bool checked);
    void on_checkBox_14_clicked(bool checked);
    void on_checkBox_15_clicked(bool checked);
    void on_checkBox_16_clicked(bool checked);
    void on_checkBox_17_clicked(bool checked);
    void on_checkBox_18_clicked(bool checked);
    void on_checkBox_19_clicked(bool checked);
    void on_checkBox_20_clicked(bool checked);
    void on_checkBox_21_clicked(bool checked);
    void on_checkBox_22_clicked(bool checked);
    void on_checkBox_23_clicked(bool checked);
    void on_checkBox_24_clicked(bool checked);
    void on_checkBox_25_clicked(bool checked);
    void on_checkBox_26_clicked(bool checked);
    void on_checkBox_27_clicked(bool checked);
    void on_checkBox_28_clicked(bool checked);
    void on_checkBox_29_clicked(bool checked);
    void on_checkBox_30_clicked(bool checked);
    void on_checkBox_31_clicked(bool checked);
    void on_checkBox_32_clicked(bool checked);
    void on_checkBox_33_clicked(bool checked);
    void on_checkBox_34_clicked(bool checked);
    void on_checkBox_35_clicked(bool checked);
    void on_checkBox_36_clicked(bool checked);
    void on_checkBox_37_clicked(bool checked);
    void on_checkBox_38_clicked(bool checked);
    void on_checkBox_39_clicked(bool checked);
    void on_checkBox_40_clicked(bool checked);
    void on_checkBox_41_clicked(bool checked);
    void on_checkBox_42_clicked(bool checked);
    void on_checkBox_43_clicked(bool checked);
    void on_checkBox_44_clicked(bool checked);
    void on_checkBox_45_clicked(bool checked);
    void on_checkBox_46_clicked(bool checked);
    void on_checkBox_47_clicked(bool checked);
    void on_checkBox_48_clicked(bool checked);

    void on_pushButton_5_clicked();

signals:
    void showEventPlanner();
    void quit();
};

#endif // EVENTADMINMODE_H
