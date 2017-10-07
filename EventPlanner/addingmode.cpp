#include "addingmode.h"
#include "ui_addingmode.h"
#include "eventplanner.h"
#include <QString>
#include <QList>

//Adding Mode - Constructor
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
    ui->wListEvents->clear();
    EventIndex = 0;
    int number = 1;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
        ui->wListEvents->addItem(QString::number(number)+". "+(*it)->printEvent());
        number++;
    }
}

//Destructor
AddingMode::~AddingMode()
{
    session->saveEventsToFile();
    delete ui;
}

//Show Form
void AddingMode::receiveshow()
{
    if (ui->wListEvents->count() != session->numberOfEvents()) {
        ui->wListEvents->clear();
        int number = 1;
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
           ui->wListEvents->addItem(QString::number(number)+". " + (*it)->printEvent());
        number++;
        }
    } else {
        for(int i = 0; i < ui->wListEvents->count(); i++) {
           ui->wListEvents->item(i)->setHidden(false);
        }
    }

    this->show();
}

//Back button
void AddingMode::on_btnBack_clicked()
{
    ui->wListTimeslots->clear();
    ui->wListAttendees->clear();
    this->hide();
    EventName = "";
    emit showEventPlanner();
}

//(Listener) On Event Selected
void AddingMode::on_wListEvents_clicked(const QModelIndex &index)
{
    /* TODO
     * - Update Date data in Calendar widget
     * - Update Timeslots list and Attendees list according to DATE within event instead of Event itself
     *      - Change Flow of list updating from
     *          |Event->Timeslots->Attendees)     |
     *
     *        to
     *          |Event->Date->Timeslots->Attendees|
     *          |     ->Tasks->[Show Task View]   |
     */

    //Clear lists (Timeslots, Attendees, Tasks)
    ui->wListTimeslots->clear();
    ui->wListAttendees->clear();
    ui->wListTasks->clear();

    //Find the clicked event from the data stored in the session, then populate the Lists in the flow lined out above.
    int count = 0;
    bool first = true;
    EventIndex = index.row();
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == EventIndex)
       {
           //Retrieve & populate Timeslots and respective Attendees
           foreach (int slot, (*it)->getTimeSlots()) {
               ui->wListTimeslots->addItem(helpermethods::toTimeSlot(slot, format));
               if (first) {
                   first = false;
                   ui->wListTimeslots->setCurrentRow(1);
                   QStringList names = (*it)->getAttendeesAtTimeslot(slot);
                   QString name;
                   foreach(name, names) {
                       ui->wListAttendees->addItem(name);
                   }
               }
           }
           //Retrieve & populate Tasks list
           foreach (QString task, (*it)->getTasks()) {
               ui->wListTasks->addItem(task);
           }
           break;
       }
       count++;
    }

}


void AddingMode::on_wListTimeslots_clicked(const QModelIndex &index) {

    ui->wListAttendees->clear();
    int count = 0;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
    {
         if(count == EventIndex)
         {
             int slot;
             foreach (slot, (*it)->getTimeSlots()) {
                 if (helpermethods::toTimeSlot(slot, format) == ui->wListTimeslots->item(index.row())->text()) {
                    QStringList names = (*it)->getAttendeesAtTimeslot(slot);
                    QString name;
                    foreach(name, names) {
                        ui->wListAttendees->addItem(name);
                    }
                 }
             }
             break;
         }
         count++;
     }
}

void AddingMode::on_wListTasks_clicked(const QModelIndex &index) {

}


// Need to change this up....
void AddingMode::on_addToTimeSlotButton_clicked(){
    if (ui->wListEvents->count() == 0) {
        return;
    }

    QString selectedTime = ui->wListTimeslots->currentItem()->text();
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
        for(int i = 0; i < ui->wListEvents->count(); i++)
        {ui->wListEvents->item(i)->setHidden(false);}
        on_wListTimeslots_clicked(ui->wListTimeslots->currentIndex());
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;}
}
