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
    int number = 1;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
        ui->listWidget->addItem(QString::number(number)+". "+(*it)->printEvent());
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
    ui->listWidget_3->clear();
    this->hide();
    EventName = "";
    emit showEventPlanner();
}

void AddingMode::receiveshow()
{
    if (ui->listWidget->count() != session->numberOfEvents()) {
        ui->listWidget->clear();
        int number = 1;
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
           ui->listWidget->addItem(QString::number(number)+". " + (*it)->printEvent());
        number++;
        }
    } else {
        for(int i = 0; i < ui->listWidget->count(); i++) {
           ui->listWidget->item(i)->setHidden(false);
        }
    }

    this->show();
}

void AddingMode::on_listWidget_clicked(const QModelIndex &index)
{
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    int count =0;
    bool first = true;
    EventIndex = index.row();
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == EventIndex)
       {
           foreach (int slot, (*it)->getTimeSlots()) {
               ui->listWidget_2->addItem(helpermethods::toTimeSlot(slot, format));
               if (first) {
                   first = false;
                   ui->listWidget_2->setCurrentRow(1);
                   QStringList names = (*it)->getAttendeesAtTimeslot(slot);
                   QString name;
                   foreach(name, names) {
                       ui->listWidget_3->addItem(name);
                   }
               }
           }
           break;
       }
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
             int slot;
             foreach (slot, (*it)->getTimeSlots()) {
                 if (helpermethods::toTimeSlot(slot, format) == ui->listWidget_2->item(index.row())->text()) {
                    QStringList names = (*it)->getAttendeesAtTimeslot(slot);
                    QString name;
                    foreach(name, names) {
                        ui->listWidget_3->addItem(name);
                    }
                 }
             }
             break;
         }
         count++;
     }
}


// Need to change this up....
void AddingMode::on_addToTimeSlotButton_clicked(){
    if (ui->listWidget->count() == 0) {
        return;
    }

    QString selectedTime = ui->listWidget_2->currentItem()->text();
        int count = 0;
switch(QMessageBox::question(this,"Adding","Do you want to join it?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
    case QMessageBox::Ok:
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
        {
         if(count == EventIndex)
         {
             QList<attendee*> attn = (*it)->getAttendees();
             QList<int> times = (*it)->getTimeSlots();
             int slot;
             foreach(slot, times) {
                 if (helpermethods::toTimeSlot(slot, format) == selectedTime) {
                    (*it)->addAttendee(session->getUser(), slot);
                 }
             }

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
