#include "eventadminmode.h"
#include "ui_eventadminmode.h"
#include <eventplanner.h>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>
#include <QPixmap>
#include <QIcon>
#include <ctime>
#include <QString>


EventAdminMode::EventAdminMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventAdminMode),
    session(session)
{
    ui->setupUi(this);

    //initialzation for all value
    setWindowTitle("EventAdmin Mode");
    EventName = "";
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setMinimumDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
    setStyle_calendarWidget();
}

EventAdminMode::~EventAdminMode()
{
    delete ui;
}

QString EventAdminMode::Info_Collect(QString &EventName,QString person_name, int month, int day, int year)
{
    QString Now ="Do you want to create this event?\n";
    Now = Now + "Event Name:  ";
    Now = Now + person_name;
    Now = Now +"'s ";
    Now = Now + EventName;
    Now = Now + "\nDate: " + QString::number(month) + "/" + QString::number(day) + "/" + QString::number(year);
    return(Now);
}

void EventAdminMode::setStyle_calendarWidget()
{
    QPixmap go_arr(":/calendarWidget_Icon/Go_Arr.jpg");
    QPixmap back_arr(":/calendarWidget_Icon/Back_Arr.jpg");
    QIcon ButtonIcon(back_arr), ButtonIcon_2(go_arr);
    QToolButton *back = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));
    QToolButton *front = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));
    back->setIcon(ButtonIcon);
    front->setIcon(ButtonIcon_2);
}

void EventAdminMode::receiveshow()
{
    ui->startTime->clear();
    ui->endTime->clear();
    for (int i = 0; i < 48; i++) {
        if (i != 47) ui->startTime->addItem(helpermethods::toTime(i, !set12HourFormat));
        ui->endTime->addItem(helpermethods::toTime(i, !set12HourFormat));
    }
    this->show();


}

void EventAdminMode::on_backButton_clicked()
{
    on_pushButton_5_clicked();
    this->hide();
    emit showEventPlanner();
}



void EventAdminMode::on_set12Hour_clicked() // use to change times mode to 12-Hour
{
    set12HourFormat = true;
    int startIndex = ui->startTime->currentIndex();
    int endIndex = ui->endTime->currentIndex();
    ui->startTime->clear();
    ui->endTime->clear();
    for (int i = 0; i < 48; i++){
        if (i != 47) ui->startTime->addItem(helpermethods::toTime(i, !set12HourFormat));
        ui->endTime->addItem(helpermethods::toTime(i, !set12HourFormat));
    }
    ui->startTime->setCurrentIndex(startIndex);
    ui->endTime->setCurrentIndex(endIndex);
    resetTimeSlotsWidget();
}

void EventAdminMode::on_set24Hour_clicked() // use to change times mode to 24-Hour
{
    set12HourFormat = false;
    int startIndex = ui->startTime->currentIndex();
    int endIndex = ui->endTime->currentIndex();
    ui->startTime->clear();
    ui->endTime->clear();
    for (int i = 0; i < 48; i++){
        if (i != 47) ui->startTime->addItem(helpermethods::toTime(i, !set12HourFormat));
        ui->endTime->addItem(helpermethods::toTime(i, !set12HourFormat));
    }
    ui->startTime->setCurrentIndex(startIndex);
    ui->endTime->setCurrentIndex(endIndex);
    resetTimeSlotsWidget();
}

void EventAdminMode::on_addTimeSlots_clicked() {
    if (ui->startTime->currentIndex() >= ui->endTime->currentIndex()) {
        QMessageBox::critical(this, "Error with time entry", "Start time must be prior to end time.", QMessageBox::Ok,QMessageBox::Ok);
    } else {
        QString month = QString::number(ui->calendarWidget->selectedDate().month());
        QString day = QString::number(ui->calendarWidget->selectedDate().day());
        QString year = QString::number(ui->calendarWidget->selectedDate().year());
        QString dateString = month + "-" + day + "-" + year;

        QList<int> slotList;

        for (int i = ui->startTime->currentIndex(); i < ui->endTime->currentIndex() && i < 48; i++) {
            //if (slotList.indexOf(i) == -1) slotList.append(i);
        }
        resetTimeSlotsWidget();
    }
}

void EventAdminMode::on_clearTimeSlotsButton_clicked() {
    timeslots.clear();
    resetTimeSlotsWidget();
}

void EventAdminMode::on_eventNameTextBox_textEdited(const QString &arg1)
{   //get edited string(name) from user
    EventName = arg1;
}

void EventAdminMode::on_saveButton_clicked()
{
    bool isTimeSlotSelected = false;

    if (timeslots.length() > 0) isTimeSlotSelected = true;

    if(!isTimeSlotSelected) {
        QMessageBox::warning(this,"Warning!!","No time slots were added to the event.");
    } else if(EventName == "") {
        QMessageBox::warning(this,"Warning!!","No event name was entered.");
    } else if (EventName.length() > 50) {
        QMessageBox::warning(this,"Warning!!","Event name must be less than 50 characters long.");
    } else {

        switch(QMessageBox::question(this,"Create Event",Info_Collect(EventName, session->getUser(), ui->calendarWidget->selectedDate().month(),
                                                                      ui->calendarWidget->selectedDate().day(),
                                                                      ui->calendarWidget->selectedDate().year()),
                             QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
        {
        case QMessageBox::Ok:
        {
            attendee* attn = new attendee();
            attn->setAttendeeName(session->getUser());
            attn->setAvailability(timeslots);
            attn->setEventID(session->numberOfEvents() + 1); // THIS COULD CAUSE PROBLEMS ON EMPTY LIST?
            QList<attendee*> aList;
            aList.append(attn);

            QList<int> slotList;
            for(int i = 0; i < timeslots.size(); i++) {
                foreach (int j, timeslots[i]) {
                    slotList.append(j + (48 * i));
                }
            }   // JUST FINISHED ADDING THIS. WALKING TO TOMMY NOW
                // TODO: FINISH THIS

            session->addEvent(session->getUser(), EventName, session->numberOfEvents() + 1, eventDays , timeslots, aList);
            session->saveEventsToFile();
            on_pushButton_5_clicked();
            break;
        }
        default:
            break;
        }
    }
    return;
}

void EventAdminMode::on_pushButton_5_clicked()
{
    ui->eventNameTextBox->setText("");
    ui->startTime->setCurrentIndex(0);
    ui->endTime->setCurrentIndex(0);
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setSelectedDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
    timeslots.clear();
    resetTimeSlotsWidget();
    EventName = "";
}

void EventAdminMode::resetTimeSlotsWidget() {
    ui->timeSlotsWidget->clear();
    int slot;
    foreach(slot, timeslots) {
        ui->timeSlotsWidget->addItem(helpermethods::toTimeSlot(slot, !set12HourFormat));
    }
}

