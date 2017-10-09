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
    setWindowTitle("Event Viewer");
    ui->wListEvents->clear();
    ui->gbAdmin->setStyleSheet("background-color: #e2edff;");
    ui->gbSignup->setStyleSheet("background-color: #fff4e0;");
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
        ui->gbAdmin->show();

        loadAdminTasks();
        updateDate(false);

    } else {
        // Sign-up Mode

        ui->gbSignup->show();

        updateTasksList();
        updateDate(true);
    }

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

void AddingMode::updateDate(bool mode) { // True = usermode, false = admin mode
    foreach(QString day, EventDays) {
        if (mode) {
            ui->wListDates->addItem(day);
        } else {
            ui->wListAdminDates->addItem(day);
        }
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

void AddingMode::on_wListAdminDates_clicked(const QModelIndex &index) {
    ui->lblAdminTitle1->show();
    ui->lblAdminTitle2->clear();
    ui->lblAdminAttn->show();
    ui->lblAdminTimeframe->show();
    ui->lblAdminTimeframe->clear();
    ui->lblAdminAttn->clear();
    ui->gbAttendees->show();
    ui->wListAttendees->clear();
    dayAttendees.clear();

    EventDateIndex = index.row();

    ui->gbAttendees->setTitle(EventDays[EventDateIndex] + " Attendees");

    loadAdminData();
}

void AddingMode::loadAdminData() {
    // Need to load Attendees and event timeframe here

    foreach (attendee* att, EventAttendees) {
        // Add attendee name ONLY if they are attending on this date.
        // Let's keep track of which attendees we have added

        foreach (int slot, att->getAvailability()) {
            if (slot / 48 == EventDateIndex) {
                // They are on this date
                dayAttendees.append(att); // Using this list will make it easier to handle click events on wListAttendees
                ui->wListAttendees->addItem(att->getAttendeeName());
                break;
            }
        }
    }

    QList<int> daySlots; // This will keep track of which timeslots correspond to this day

    bool found = false;
    foreach(int slot, EventTimeslots) {
        if (EventDateIndex == 0) {
            if (slot > 47) break;
            daySlots.append(slot);
        } else if (slot / 48 == EventDateIndex) {
            found = true;
            daySlots.append(slot);
        } else if (found) {
            break;
        }
    }

    QString timestring = helpermethods::getTimeString(daySlots, format);
    qDebug() << timestring;
    ui->lblAdminTitle1->setText(EventDays[EventDateIndex] + " Timeframe");
    ui->lblAdminTimeframe->setText(timestring);
}

void AddingMode::on_wListAttendees_clicked(const QModelIndex &index) {
    ui->lblAdminTitle2->show();

    int ind = index.row();

    ui->lblAdminTitle2->setText(dayAttendees[ind]->getAttendeeName() + "'s Availability");

    QList<int> daySlots;

    bool found = false;
    foreach(int slot, dayAttendees[ind]->getAvailability()) {
        if (EventDateIndex == 0){
            if (slot > 47) break;
            daySlots.append(slot);
        } else if (slot / 48 == EventDateIndex) {
            found = true;
            daySlots.append(slot);
        } else if (found) {
            break;
        }
    }

    ui->lblAdminAttn->setText(helpermethods::getTimeString(daySlots, format));
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
                ui->wListSignupSlots->addItem(helpermethods::toTimeSlot(slot, format));
            }
        } else if (slot / 48 == EventDateIndex) {
            found = true;
            thisDaysTimeslots.append(slot);
            if (totalUserAvail.contains(slot)) {
                userAvail.append(slot);
            } else {
                ui->wListSignupSlots->addItem(helpermethods::toTimeSlot(slot, format));
            }
        } else if (found) {
            break;
        }
    }

    QString timeframe = helpermethods::getTimeString(thisDaysTimeslots, format);
    QString userAvailability = helpermethods::getTimeString(userAvail, format);

    ui->lblTimeframe->setText(timeframe);
    ui->lblUserAvail->setText(userAvailability);

}

void AddingMode::updateAttendees(std::list<Event*>::iterator it, int atSlot) {
    foreach(QString name, (*it)->getAttendeesAtTimeslot(atSlot))
        ui->wListAttendees->addItem(name);
}

void AddingMode::loadAdminTasks() {
    ui->wListAdminTasks->clear();
    EventPossibleTasks = false;

    ui->lblTasks->hide();

    ui->lblTasks->setStyleSheet("QLabel { color : red; }");

    int count = 0;
    foreach (QString task, EventTasks) {
        ui->wListAdminTasks->addItem(task);
        ui->wListAdminTasks->item(count)->setForeground(Qt::red);
        count++;
        ui->lblTasks->show();
        EventPossibleTasks = true;
    }

    foreach(attendee* att, EventAttendees) {
        foreach(QString task, att->getTasks()) {
            QString finishedTaskString = "'" + task + "' : " + att->getAttendeeName() + " has volunteered.";
            ui->wListAdminTasks->addItem(finishedTaskString);
            ui->wListAdminTasks->item(count)->setForeground(Qt::darkGreen);
            ui->wListAdminTasks->item(count)->setFlags(!Qt::ItemIsEditable & !Qt::ItemIsSelectable);
            count++;
        }
    }

    if (ui->wListAdminTasks->count() > 0) {
        ui->wListAdminTasks->item(0)->setSelected(true);
    }
    ui->wListAdminTasks->setFocus();
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

void AddingMode::on_btnAdminVolunteer_clicked() {
    if (!EventPossibleTasks) return;

    QString selectedTask = ui->wListAdminTasks->currentItem()->text();

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
            loadAdminTasks();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
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

void AddingMode::resetView() {
    ui->gbSignup->hide();
    ui->gbAdmin->hide();
    ui->wListAdminDates->clear();
    ui->wListAdminTasks->clear();
    ui->wListAttendees->clear();
    ui->wListSignupSlots->clear();
    ui->wListTasks->clear();
    ui->wListDates->clear();
    ui->lblTimeframe->clear();
    ui->lblUserAvail->clear();
    ui->lblTitle1->hide();
    ui->lblTitle2->hide();
    ui->lblAdminTitle1->hide();
    ui->lblAdminTitle2->hide();
    ui->lblAdminTimeframe->hide();
    ui->lblAdminAttn->hide();
    ui->gbAttendees->hide();

    dayAttendees.clear();
}

void AddingMode::on_btnAll_clicked() {
    if (ui->wListSignupSlots->count() == 0) return;
    if (ui->wListSignupSlots->selectedItems().count() == ui->wListSignupSlots->count()) {
        ui->wListSignupSlots->clearSelection();
    } else {
        ui->wListSignupSlots->selectAll();
        ui->wListSignupSlots->setFocus();
    }
}

void AddingMode::on_addToTimeSlotButton_clicked(){

    // TODO Allow multiple selection at once.

    if (ui->wListSignupSlots->count() == 0) return;

    QList<QListWidgetItem *> selection = ui->wListSignupSlots->selectedItems();

    if (selection.count() == 0) return;

    // Create the confirmation string THIS IS REDUNDANT BECAUSE OF THE STUFF LATER BUT OH WELL.
    int slot;
    QList<QString> addSlotsString;
    QList<int> addSlots;
    foreach(QListWidgetItem* item, selection) {
       QString selectedTime = item->text();
       foreach(slot, EventTimeslots) {
           if (helpermethods::toTimeSlot(slot, format) == selectedTime && slot / 48 == EventDateIndex) {
               addSlots.append(slot);
               break;
           }
       }
    }

    QString selectionString = helpermethods::getTimeString(addSlots, format);

    int count = 0;
    switch(QMessageBox::question(this,"Adding","Are you sure you want to add " + selectionString + " on " + EventDays[EventDateIndex] + " to your availability?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
        case QMessageBox::Ok:
            for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
            {
             if(count == EventIndex)
             {
                (*it)->addAttendee(session->getUser(), addSlots);

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
