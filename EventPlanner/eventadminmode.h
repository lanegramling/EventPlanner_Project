#ifndef EVENTADMINMODE_H
#define EVENTADMINMODE_H
#include <QMainWindow>
#include <QDebug>
#include "session.h"
#include "timeslot.h"
namespace Ui {
class EventAdminMode;
}
class EventAdminMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit EventAdminMode(Session *session, QWidget *parent = 0);
    ~EventAdminMode();


    QString Info_Collect(QString &EventName,QString &person_name, int month, int day, int year);
    // use to make all Information to a string, used for "Make Sure"

    void setStyle_calendarWidget();
private:
    Ui::EventAdminMode *ui;

    //member variable: use to store the temp information from user
    int months; // month
    int days;   // day
    QString EventName; // Event Name
    QString person_name; //Event creater name
    const QStringList TIME_ARRAY_12H = {"12:00 AM", "12:30 AM", "1:00 AM", "1:30 AM", "2:00 AM", "2:30 AM", "3:00 AM", "3:30 AM",
                                  "4:00 AM", "4:30 AM", "5:00 AM", "5:30 AM", "6:00 AM", "6:30 AM", "7:00 AM", "7:30 AM",
                                  "8:00 AM", "8:30 AM","9:00 AM", "9:30 AM", "10:00 AM", "10:30 AM", "11:00 AM", "11:30 AM",
                                  "12:00 PM", "12:30 PM", "1:00 PM", "1:30 PM", "2:00 PM", "2:30 PM", "3:00 PM", "3:30 PM",
                                  "4:00 PM", "4:30 PM", "5:00 PM", "5:30 PM", "6:00 PM", "6:30 PM", "7:00 PM", "7:30 PM",
                                  "8:00 PM", "8:30 PM","9:00 PM", "9:30 PM", "10:00 PM", "10:30 PM", "11:00 PM", "11:30 PM"};
    const QStringList TIME_ARRAY_24H = {"00:00", "00:30", "01:00", "01:30", "02:00", "02:30", "03:00", "03:30",
                                       "04:00", "04:30", "05:00", "05:30", "06:00", "06:30", "07:00", "07:30",
                                       "08:00", "08:30", "09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
                                       "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30",
                                       "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30",
                                       "20:00", "20:30", "21:00", "21:30", "22:00", "22:30", "23:00", "23:30"};

    Session *session;
    bool set12HourFormat = true;
    QList<TimeSlot> timeSlots;
    void resetTimeSlotsWidget();
    void on_pushButton_5_clicked();// member function

private slots:
    void receiveshow();

    void on_saveButton_clicked();
    void on_backButton_clicked();
    void on_set12Hour_clicked();
    void on_set24Hour_clicked();
    void on_addTimeSlots_clicked();
    void on_clearTimeSlotsButton_clicked();

    void on_eventNameTextBox_textEdited(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);

signals:
    void showEventPlanner();
    void quit();
};

#endif // EVENTADMINMODE_H
