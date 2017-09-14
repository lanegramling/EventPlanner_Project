#include "eventadminmode.h"
#include "ui_eventadminmode.h"
#include <eventplanner.h>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>
#include <QPixmap>
#include <QIcon>
#include <ctime>


EventAdminMode::EventAdminMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventAdminMode),
    session(session)
{
    ui->setupUi(this);
    for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
        TimeSlot tempTimeSlot;
        if (i != TIME_SLOTS_LENGTH -1) {
            tempTimeSlot.setTime12Hour(TIME_ARRAY_12H.at(i) + "-" + TIME_ARRAY_12H.at(i+1));
            tempTimeSlot.setTime24Hour(TIME_ARRAY_24H.at(i) + "-" + TIME_ARRAY_24H.at(i+1));
        } else {
            tempTimeSlot.setTime12Hour(TIME_ARRAY_12H.at(i) + "-12:00 AM");
            tempTimeSlot.setTime24Hour(TIME_ARRAY_24H.at(i) + "-00:00");
        }
        timeSlots.push_back(tempTimeSlot);
    }
    //initialzation for all value
    setWindowTitle("EventAdmin Mode");
    EventName = "N";
    person_name = "/A";
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setMinimumDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
    setStyle_calendarWidget();
}

EventAdminMode::~EventAdminMode()
{
    session->saveEventsToFile();
    delete ui;
}

QString EventAdminMode::Info_Collect(QString &EventName,QString &person_name, int month, int day, int year)
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
    for (int i = 0; i < TIME_ARRAY_12H.size(); i++){
        ui->startTime->addItem(TIME_ARRAY_12H.at(i));
    }
    for(int i = 0; i < TIME_ARRAY_12H.size(); i++) {
        ui->endTime->addItem(TIME_ARRAY_12H.at(i));
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
    for (int i = 0; i < TIME_ARRAY_12H.size()-1; i++){
        ui->startTime->addItem(TIME_ARRAY_12H.at(i));
    }
    for(int i = 1; i < TIME_ARRAY_12H.size(); i++) {
        ui->endTime->addItem(TIME_ARRAY_12H.at(i));
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
    for (int i = 0; i < TIME_ARRAY_24H.size()-1; i++){
        ui->startTime->addItem(TIME_ARRAY_24H.at(i));
    }
    for(int i = 0; i < TIME_ARRAY_24H.size(); i++) {
        ui->endTime->addItem(TIME_ARRAY_24H.at(i));
    }
    ui->startTime->setCurrentIndex(startIndex);
    ui->endTime->setCurrentIndex(endIndex);
    resetTimeSlotsWidget();
}

void EventAdminMode::on_addTimeSlots_clicked() {
    if (ui->startTime->currentIndex() >= ui->endTime->currentIndex()) {
        QMessageBox::critical(this, "Error with time entry", "Start time must be prior to end time.", QMessageBox::Ok,QMessageBox::Ok);
    } else {
        for (int i = ui->startTime->currentIndex(); i < ui->endTime->currentIndex() && i < TIME_SLOTS_LENGTH; i++) {
            timeSlots[i].setTrue();
        }
        resetTimeSlotsWidget();
    }
}

void EventAdminMode::on_clearTimeSlotsButton_clicked() {
    for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
        timeSlots[i].clearTimeSlot();
    }
    resetTimeSlotsWidget();
}

void EventAdminMode::on_eventNameTextBox_textEdited(const QString &arg1)
{   //get edited string(name) from user
    EventName = arg1;
}

void EventAdminMode::on_saveButton_clicked()
{
    bool isTimeSlotSelected = false;
    for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
        if (timeSlots.at(i).isSelected()) {
            isTimeSlotSelected = true;
            break;
        }
    }
    if((!isTimeSlotSelected)||(EventName == "N")||(person_name == "/A"))
        {QMessageBox::warning(this,"Warning!!","Please Check Name and Your times!!!");}
    else if (person_name.contains("\"")){
        {QMessageBox::warning(this,"Invalid User Name!","User name may not contain quotation marks.");}
    } else {
    switch(QMessageBox::question(this,"Create Event",Info_Collect(EventName, person_name, ui->calendarWidget->selectedDate().month(),
                                                                  ui->calendarWidget->selectedDate().day(),
                                                                  ui->calendarWidget->selectedDate().year()),
                         QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
            if (timeSlots.at(i).isSelected()) {
                timeSlots[i].addAttendee(person_name);
            }
        }
        session->addEvent(person_name, EventName, ui->calendarWidget->selectedDate().month(),
                          ui->calendarWidget->selectedDate().day(), ui->calendarWidget->selectedDate().year(), timeSlots);
        session->saveEventsToFile();
        on_pushButton_5_clicked();
        session->saveEventsToFile();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }}
    return;
}

void EventAdminMode::on_lineEdit_2_textChanged(const QString &arg1)
{person_name = arg1;}

void EventAdminMode::on_pushButton_5_clicked()
{
    ui->eventNameTextBox->setText("");
    ui->lineEdit_2->setText("");
    ui->startTime->setCurrentIndex(0);
    ui->endTime->setCurrentIndex(0);
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setSelectedDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
    for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
        timeSlots[i].clearTimeSlot();
    }
    resetTimeSlotsWidget();
    EventName = "N";
    person_name = "/A";  
}

void EventAdminMode::resetTimeSlotsWidget() {
    ui->timeSlotsWidget->clear();
    for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
        if (timeSlots.at(i).isSelected()) {
            if (set12HourFormat) {
                ui->timeSlotsWidget->addItem(timeSlots.at(i).getTime12Hour());
            } else {
                ui->timeSlotsWidget->addItem(timeSlots.at(i).getTime24Hour());
            }
        }
    }
}

