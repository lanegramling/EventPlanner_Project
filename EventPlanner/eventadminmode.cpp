#include "eventadminmode.h"
#include "ui_eventadminmode.h"
#include <eventplanner.h>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <ctime>

EventAdminMode::EventAdminMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventAdminMode),
    session(session)
{
    ui->setupUi(this);

    //initialzation for all value
    setWindowTitle("EventAdmin Mode");
    EventName = "N";
    person_name = "/A";
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setMinimumDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
}

EventAdminMode::~EventAdminMode()
{
    session->saveEventsToFile();
    delete ui;
}

QString EventAdminMode::Info_Collect(QString &EventName,QString &person_name, int month, int day, int year, QString startTime, QString endTime)
{
    QString Now ="Do you want to create this event?\n";
    Now = Now + "Event Name:  ";
    Now = Now + person_name;
    Now = Now +"'s ";
    Now = Now + EventName;
    Now = Now + "\nDate: " + QString::number(month) + "/" + QString::number(day) + "/" + QString::number(year);
    Now = Now + "\ntimes: " + startTime + " - " + endTime;
    return(Now);
}

void EventAdminMode::receiveshow()
{
    ui->startTime->clear();
    ui->endTime->clear();
    for (int i = 0; i < TIME_ARRAY_12H.size()-1; i++){
        ui->startTime->addItem(TIME_ARRAY_12H.at(i));
    }
    for(int i = 1; i < TIME_ARRAY_12H.size(); i++) {
        ui->endTime->addItem(TIME_ARRAY_12H.at(i));
    }
    ui->endTime->setCurrentIndex(0);
    this->show();


}

void EventAdminMode::on_backButton_clicked()
{
    on_pushButton_5_clicked();
    session->saveEventsToFile();
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
    for(int i = 1; i < TIME_ARRAY_24H.size(); i++) {
        ui->endTime->addItem(TIME_ARRAY_24H.at(i));
    }
    ui->startTime->setCurrentIndex(startIndex);
    ui->endTime->setCurrentIndex(endIndex);
}

void EventAdminMode::on_eventNameTextBox_textEdited(const QString &arg1)
{   //get edited string(name) from user
    EventName = arg1;
}

void EventAdminMode::on_startTime_currentIndexChanged(int index) {
    int endIndex = ui->endTime->currentIndex();
    int endSize = ui->endTime->count();
    ui->endTime->clear();
    if (set12HourFormat){
        for(int i = index+1; i < TIME_ARRAY_12H.size(); i++) {
            ui->endTime->addItem(TIME_ARRAY_12H.at(i));
        }
    } else {
        for(int i = index+1; i < TIME_ARRAY_24H.size(); i++) {
            ui->endTime->addItem(TIME_ARRAY_24H.at(i));
        }
    }
    if (ui->endTime->count() >= endSize) {
        ui->endTime->setCurrentIndex(ui->endTime->count() - endSize + endIndex);
    } else if (endIndex - (endSize - ui->endTime->count()) > 0) {
        ui->endTime->setCurrentIndex(endIndex - (endSize - ui->endTime->count()));
    }
}

void EventAdminMode::on_saveButton_clicked()
{
    if((EventName == "N")||(person_name == "/A"))
    {QMessageBox::warning(this,"Warning!!","Please Check Name and Your times!!!");}
    else{
    switch(QMessageBox::question(this,"Create Event",Info_Collect(EventName, person_name, ui->calendarWidget->selectedDate().month(),
                                                            ui->calendarWidget->selectedDate().day(), ui->calendarWidget->selectedDate().year(),
                                                            ui->startTime->currentText(), ui->endTime->currentText()),
                         QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        session->addEvent(person_name,EventName, ui->calendarWidget->selectedDate().month(),
                          ui->calendarWidget->selectedDate().day(), ui->calendarWidget->selectedDate().year(),
                          ui->startTime->currentText(), ui->endTime->currentText());
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
{
 person_name = arg1;
}

void EventAdminMode::on_pushButton_5_clicked()
{
    ui->eventNameTextBox->setText("");
    ui->lineEdit_2->setText("");
    EventName = "N";
    person_name = "/A";  
}
