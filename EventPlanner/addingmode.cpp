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
    resetView();
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
    resetView();
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

    //Prepare for repopulation of lists (Timeslots, Attendees, Tasks)

    // CHECK IF WE ARE ADMIN OR NOT

    resetView();

    EventIndex = index.row();
    loadEventData(EventIndex);

    if (session->getUser() == EventCreator) {
        // Admin Mode


    } else {
        // Sign-up Mode

        ui->gbSignup->show();

        updateTasksList();
        updateDate();
    }













//    //Find the newly selected from the data stored in the session, then populate the Lists in the flow lined out above.
//    int count = 0;
//    EventIndex = index.row();
//    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
//       if(count == EventIndex)
//       {
//           //Retrieve & populate Timeslots and respective Attendees
//           foreach (int slot, (*it)->getTimeSlots()) {
//               ui->wListTimeslots->addItem(helpermethods::toTimeSlot(slot, format));
//               if (slot == 0) { //Fill rest of fields with first timeslot's info.
//                   ui->wListTimeslots->setCurrentRow(1);
//                   QStringList names = (*it)->getAttendeesAtTimeslot(slot);
//                   QString name;
//                   foreach(name, names) {
//                       ui->wListAttendees->addItem(name);
//                   }
//               }
//           }
//           //Retrieve & populate Tasks list
//           foreach (QString task, (*it)->getTasks()) {
//               ui->wListTasks->addItem(task);
//           }
//           break;
//       }
//       count++;
//    }

}

void AddingMode::loadEventData(int index) {
    int count = 0;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == index)
       {
           EventCreator = (*it)->getOwner();
           EventName = (*it)->getEventName();
           EventTimeslots = (*it)->getTimeSlots();
           EventAttendees = (*it)->getAttendees();
           EventTasks = (*it)->getTasks();
           EventDays = (*it)->getDays();

           getUserIndex();
           break;
       }
       count++;
    }
}

void AddingMode::getUserIndex() {
    QString currentUser = session->getUser();

    qDebug() << currentUser;
    int count = 0;
    foreach(attendee* att, EventAttendees) {
        if (att->getAttendeeName() == currentUser) {
            EventUserIndex = count;
            return;
        }
        count++;
    }

    // Only reached if the current user has not signed up for the event
    EventUserIndex = -1;
}

//Run on changing of an event
void AddingMode::updateEvent(int EventIndex) {
    int count = 0;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == EventIndex) //Found selected event -- now populate
       {
           EventCreator = (*it)->getOwner();
           //firstDateofEvent = ... ;
           //updateDate(firstDateofEvent); -- Will move updateTimeslots(it) from below to within this method.
           //updateTimeslots(it);
           //updateAttendees(it, 1); //Start at Timeslot 0 for showing attendees
           //updateTasksList(it);
       }
       count++;
    }
    ui->wListTimeslots->setCurrentRow(1);
}

void AddingMode::updateDate() {
    foreach(QString day, EventDays) {
        ui->wListDates->addItem(day);
    }
}

void AddingMode::on_wListDates_clicked(const QModelIndex &index) {
    ui->lblTitle1->show();
    ui->lblTitle2->show();
    ui->lblTimeframe->clear();
    ui->lblUserAvail->clear();
    ui->wListSignupSlots->clear();

    EventDateIndex = index.row();

    loadUserAvailability();
}

void AddingMode::loadUserAvailability() {
    QList<int> thisDaysTimeslots;
    QList<int> totalUserAvail;
    if (EventUserIndex != -1) {
        totalUserAvail = EventAttendees[EventUserIndex]->getAvailability();
    }


    QList<int> userAvail;
    QList<int> signupAvail;
    bool found = false;
    foreach(int slot, EventTimeslots) {
        if (EventDateIndex == 0) {
            if (slot > 47) break;
            thisDaysTimeslots.append(slot);
            if (totalUserAvail.contains(slot)) {
                userAvail.append(slot);
            } else {
                ui->wListSignupSlots->addItem(helpermethods::toTimeSlot(slot, false));
            }
        } else if (slot / 48 == EventDateIndex) {
            found = true;
            thisDaysTimeslots.append(slot);
            if (totalUserAvail.contains(slot)) {
                userAvail.append(slot);
            } else {
                ui->wListSignupSlots->addItem(helpermethods::toTimeSlot(slot, false));
            }
        } else if (found) {
            break;
        }
    }

    QString timeframe = helpermethods::getTimeString(thisDaysTimeslots, false);
    QString userAvailability = helpermethods::getTimeString(userAvail, false);

    ui->lblTimeframe->setText(timeframe);
    ui->lblUserAvail->setText(userAvailability);

    if (ui->wListSignupSlots->count() > 0) {
        ui->wListSignupSlots->item(0)->setSelected(true);
    }
    ui->wListSignupSlots->setFocus();
}

void AddingMode::updateTimeslots(std::list<Event*>::iterator it) {
    foreach (int slot, (*it)->getTimeSlots())
        ui->wListTimeslots->addItem(helpermethods::toTimeSlot(slot, format));
}
void AddingMode::updateAttendees(std::list<Event*>::iterator it, int atSlot) {
    foreach(QString name, (*it)->getAttendeesAtTimeslot(atSlot))
        ui->wListAttendees->addItem(name);
}

void AddingMode::updateTasksList() {
    ui->wListTasks->clear();
    EventPossibleTasks = false;
    foreach (QString task, EventTasks) {
        ui->wListTasks->addItem(task);
        EventPossibleTasks = true;
    }

    int count = ui->wListTasks->count();
    foreach (attendee* att, EventAttendees) {
        foreach(QString task, att->getTasks()) {
            QString finishedTaskString = "'" + task + "' : " + att->getAttendeeName() + " has volunteered.";
            ui->wListTasks->addItem(finishedTaskString);
            ui->wListTasks->item(count)->setForeground(Qt::darkGreen);
            ui->wListTasks->item(count)->setFlags(!Qt::ItemIsEditable & !Qt::ItemIsSelectable);
            count++;
        }
    }
    if (ui->wListTasks->count() > 0) {
        ui->wListTasks->item(0)->setSelected(true);
    }
    ui->wListTasks->setFocus();
}

void AddingMode::on_btnVolunteer_clicked() {
    if (!EventPossibleTasks) return;

    if (EventUserIndex == -1) {
        QMessageBox::critical(this, "Error", "You cannot volunteer for a task in an event you are NOT available for.", QMessageBox::Ok,QMessageBox::Ok);

        return;
    }

    QString selectedTask = ui->wListTasks->currentItem()->text();

    int count = 0;

    switch(QMessageBox::question(this,"Adding","Are you sure you want to volunteer to '" + selectedTask + "'?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
        case QMessageBox::Ok:
            for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
            {
             if(count == EventIndex)
             {
                (*it)->removeTask(selectedTask);
                (*it)->getAttendees()[EventUserIndex]->addTask(selectedTask);
                break;
             }
               count++;
            }
            session->saveEventsToFile();
            loadEventData(EventIndex);
            updateTasksList();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void AddingMode::on_wListTimeslots_clicked(const QModelIndex &index) {
    ui->wListAttendees->clear();
    int count = 0;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
    {
         if(count == EventIndex) {
             foreach (int slot, (*it)->getTimeSlots())
                 if (helpermethods::toTimeSlot(slot, format) == ui->wListTimeslots->item(index.row())->text())
                    updateAttendees(it, slot);
             break;
         }
         count++;
     }

}

void AddingMode::resetView() {
    ui->gbSignup->hide();
    //ui->gbAdmin->hide();
    ui->wListTimeslots->clear();
    ui->wListSignupSlots->clear();
    ui->wListTasks->clear();
    ui->wListDates->clear();
    ui->lblTimeframe->clear();
    ui->lblUserAvail->clear();
    ui->lblTitle1->hide();
    ui->lblTitle2->hide();
}

//void AddingMode::on_wListTimeslots_clicked(const QModelIndex &index) {
//    ui->wListAttendees->clear();
//    int count = 0;
//    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
//    {
//         if(count == EventIndex)
//         {
//             //Update rest of chain. (Attendees)
//             foreach (int slot, (*it)->getTimeSlots()) {
//                 if (helpermethods::toTimeSlot(slot, format) == ui->wListTimeslots->item(index.row())->text()) {
//                    QStringList names = (*it)->getAttendeesAtTimeslot(slot);
//                    QString name;
//                    foreach(name, names) {
//                        ui->wListAttendees->addItem(name);
//                    }
//                 }
//             }
//             break;
//         }
//         count++;
//     }
//}

void AddingMode::on_wListTasks_clicked(const QModelIndex &index) {

}


void AddingMode::on_addToTimeSlotButton_clicked(){

    // TODO Allow multiple selection at once.

    if (ui->wListSignupSlots->count() == 0) return;

    QString selectedTime = ui->wListSignupSlots->currentItem()->text();
        int count = 0;
    switch(QMessageBox::question(this,"Adding","Are you sure you want to add " + selectedTime + " on " + EventDays[EventDateIndex] + " to your availability?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
        case QMessageBox::Ok:
            for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
            {
             if(count == EventIndex)
             {
                 QList<attendee*> attn = (*it)->getAttendees();
                 int slot;
                 foreach(slot, EventTimeslots) {
                     if (helpermethods::toTimeSlot(slot, format) == selectedTime && slot / 48 == EventDateIndex) {
                        (*it)->addAttendee(session->getUser(), slot);
                         break;
                     }
                 }
             break;
             }
               count++;
            }
            session->saveEventsToFile();
            loadEventData(EventIndex);
            ui->wListSignupSlots->clear();
            loadUserAvailability();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}
