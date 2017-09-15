#include "addingmode.h"
#include "ui_addingmode.h"
#include "eventplanner.h"
#include <QString>
#include <QList>


AddingMode::AddingMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddingMode),
    session(session)
{
    ui->setupUi(this);
    setWindowTitle("Adding Mode");
    month = 1;
    day = 1;
    year = 2017;
    ui->listWidget->clear();
    EventIndex = 0;
    person_name = "";
    int number = 1;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
        ui->listWidget->addItem(QString::number(number)+". "+(*it)->getEventName());
        number++;
    }
}
AddingMode::~AddingMode()
{
    session->saveEventsToFile();
    delete ui;
}

void AddingMode::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    this->hide();
    person_name = "";
    EventName = "";
    emit showEventPlanner();
}

void AddingMode::receiveshow()
{
    if (ui->listWidget->count() != session->numberOfEvents()) {
        ui->listWidget->clear();
        int number = 1;
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
           ui->listWidget->addItem(QString::number(number)+". " + (*it)->getEventName());
        number++;
        }}
        else{
            for(int i = 0; i < ui->listWidget->count(); i++)
            {ui->listWidget->item(i)->setHidden(false);}
        }
    this->show();
}

void AddingMode::on_listWidget_clicked(const QModelIndex &index)
{
    ui->listWidget_2->clear();
    int count =0;
    EventIndex = index.row();
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == EventIndex)
       {
           for (int i = 0; i <  (*it)->getTimeSlots().length(); i++) {
                  if(((*it)->getTimeSlots()).at(i).isSelected())
                    { ui->listWidget_2->addItem(((*it)->getTimeSlots()).at(i).getTime12Hour());}
           }
           break;}
       count++;
    }
}

void AddingMode::on_listWidget_2_clicked(const QModelIndex &index) {

    ui->listWidget_3->clear();
    int count = 0;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
    {
     if(count == EventIndex)
     {
         for(int i = 0; i < TIME_SLOTS_LENGTH; i++)
         {

            if((*it)->getTimeSlots().at(i).isSelected() && (*it)->getTimeSlots().at(i).getTime12Hour() == ui->listWidget_2->item(index.row())->text()) {
                for (int j = 0; j < (*it)->getTimeSlots().at(i).getAttendees().length(); j++) {
                    ui->listWidget_3->addItem((*it)->getTimeSlots().at(i).getAttendees().at(j));
                }
                break;
            }
          }
     break;
     }
       count++;
    }
}

void AddingMode::on_addToTimeSlotButton_clicked(){

    QString selectedTime = ui->listWidget_2->currentItem()->text();
        int count = 0;
switch(QMessageBox::question(this,"Adding","Do you want to join it?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
    case QMessageBox::Ok:
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
        {
         if(count == EventIndex)
         {
             QList<TimeSlot> tempTimeSlots = (*it)->getTimeSlots();
             for(int i = 0; i < TIME_SLOTS_LENGTH; i++)
             {
                if(tempTimeSlots.at(i).isSelected() && tempTimeSlots.at(i).getTime12Hour() == selectedTime)
                {tempTimeSlots[i].addAttendee(session->getUser());
                break;
                }
              }
    // ((*it)->getTimeSlots())[index_of_list].addAttendee(person_name); we cannot do this way, i don't know why
             (*it)->setTimeSlots(tempTimeSlots);
         break;
         }
           count++;
        }
        session->saveEventsToFile();
        for(int i = 0; i < ui->listWidget->count(); i++)
        {ui->listWidget->item(i)->setHidden(false);}
        on_listWidget_2_clicked(ui->listWidget_2->currentIndex());
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;}
}
