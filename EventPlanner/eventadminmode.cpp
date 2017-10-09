#include "eventadminmode.h"
#include "ui_eventadminmode.h"



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

    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(daySelected()));

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
    daySelected();
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
    daySelected();
}

void EventAdminMode::on_addTimeSlots_clicked() { // WORKS but isn't sorted yet
    if (ui->startTime->currentIndex() >= ui->endTime->currentIndex()) {
        QMessageBox::critical(this, "Error with time entry", "Start time must be prior to end time.", QMessageBox::Ok,QMessageBox::Ok);
    } else {
        QString month = QString::number(ui->calendarWidget->selectedDate().month());
        QString day = QString::number(ui->calendarWidget->selectedDate().day());
        QString year = QString::number(ui->calendarWidget->selectedDate().year());
        QString dateString = month + "-" + day + "-" + year;

        int index = eventDays.indexOf(dateString);

        QList<int> slotList;

        if (index == -1) {

            // Let's find where this date should go.

            // If size = 0
            if (eventDays.size() == 0) {
                eventDays.append(dateString);
            } else {
                bool hasBeenAdded = false;
                for (int i = 0; i < eventDays.size(); i++) {
                    if (helpermethods::compareDates(dateString, eventDays[i])) {
                        eventDays.insert(i, dateString);
                        hasBeenAdded = true;
                        break;
                    }
                }
                if (!hasBeenAdded) {
                    eventDays.append(dateString); // If it is later than every date so far.
                }
            }
            index = eventDays.indexOf(dateString);

            // Then let's add the slots in the same spot

            for (int i = ui->startTime->currentIndex(); i < ui->endTime->currentIndex() && i < 48; i++) {
                slotList.append(i);
            }
            timeslots.insert(index, slotList);
        } else {
            for (int i = ui->startTime->currentIndex(); i < ui->endTime->currentIndex() && i < 48; i++) {
                if (!timeslots[index].contains(i)) timeslots[index].append(i);
            }
            qSort(timeslots[index]);
        }





        daySelected();
    }
}

void EventAdminMode::on_clearTimeSlotsButton_clicked() {
    timeslots.clear();
    eventDays.clear();
    daySelected();
}
void EventAdminMode::on_clearDatesButton_clicked() {
    timeslots.clear();
    eventDays.clear();
    daySelected();
}

void EventAdminMode::on_eventNameTextBox_textEdited(const QString &arg1)
{   //get edited string(name) from user
    EventName = arg1;
}

void EventAdminMode::on_taskButton_clicked() {
    if (!taskName.isEmpty()) {
        ui->tasksWidget->addItem(taskName);
        eventTasks.append(taskName);
        ui->taskEdit->clear();
    }
}

void EventAdminMode::on_taskEdit_textEdited(const QString &text) {
    taskName = text;
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
            attn->setEventID(session->numberOfEvents() + 1); // THIS COULD CAUSE PROBLEMS ON EMPTY LIST?

            QList<int> slotList;
            for(int i = 0; i < timeslots.size(); i++) {
                foreach (int j, timeslots[i]) {
                    slotList.append(j + (48 * i));
                }
            }

            attn->setAvailability(slotList);

            session->addEvent(session->getUser(), EventName, session->numberOfEvents() + 1, eventDays, eventTasks, slotList, attn);
            session->saveEventsToFile();
            on_pushButton_5_clicked();
            break;
        }
        default:
            break;
        }
    }
    ui->addedDatesWidget->clear();
    return;
}

void EventAdminMode::on_pushButton_5_clicked()
{
    ui->eventNameTextBox->clear();
    ui->tasksWidget->clear();
    ui->timeSlotsWidget->clear();
    eventTasks.clear();
    eventDays.clear();
    ui->startTime->setCurrentIndex(0);
    ui->endTime->setCurrentIndex(0);
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setSelectedDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
    timeslots.clear();
    EventName = "";
}

//Run Date list selections through the calendar widget
void EventAdminMode::on_addedDatesWidget_clicked(const QModelIndex &index){
    ui->calendarWidget->setSelectedDate(QDate::fromString(ui->addedDatesWidget->item(index.row())->text(), "M-d-yyyy" ));
    daySelected();
    ui->calendarWidget->setFocus();
}

void EventAdminMode::daySelected() {
    ui->timeSlotsWidget->clear(); //Clear timeslots from list
    //ui->addedDatesWidget->clear();
    QString selectedDate = QString::number(ui->calendarWidget->selectedDate().month()) + "-" + QString::number(ui->calendarWidget->selectedDate().day()) + "-" + QString::number(ui->calendarWidget->selectedDate().year());
    int index = eventDays.indexOf(selectedDate);
    if (index != -1) {
        foreach(int slot, timeslots[index]) {
            ui->timeSlotsWidget->addItem(helpermethods::toTimeSlot(slot, !set12HourFormat));

        }
        /*
        bool found(false);
        for (int i = ui->addedDatesWidget->count() - 1; i >= 0; i--)
            if(ui->addedDatesWidget->item(i)->text() == selectedDate){
                found = true;
                break;
            }
        if (found == false){
            ui->addedDatesWidget->addItem(selectedDate);
        }
        */
    }
    ui->addedDatesWidget->clear();
    foreach(QString day, eventDays) {
        ui->addedDatesWidget->addItem(day);
    }
}
