#ifndef ADDINGMODE_H
#define ADDINGMODE_H
#include <QMainWindow>
#include "session.h"
#include "event.h"
#include "helpermethods.h"
#include "attendee.h"
#include <list>
#include <QDebug>
namespace Ui{
class AddingMode;
}

/*!
 * \brief The AddingMode class
 * \details Class for adding availablity to an event.
 */
class AddingMode : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief AddingMode
     * \details Constructor for the Adding Mode
     * \param session
     * \param parent
     */
    explicit AddingMode(Session *session, QWidget *parent = 0);

    ~AddingMode();
private:

    /*!
     * \brief ui
     */
    Ui::AddingMode *ui;

    /*!
     * \brief EventIndex
     * \details Holds index of the selected Event.
     */
    int EventIndex;

    /*!
     * \brief EventName
     */
    QString EventName;

    QString EventCreator;

    QList<int> EventTimeslots;

    QStringList EventTasks;

    QList<attendee*> EventAttendees;

    QList<attendee*> dayAttendees;

    bool EventPossibleTasks;

    bool EventPossibleTaskSignup;

    int EventUserIndex;

    int EventDateIndex;

    QStringList EventDays;

    /*!
     * \brief month
     */
    int month;

    /*!
     * \brief year
     */
    int year;

    /*!
     * \brief day
     */
    int day;

    bool format = false;

    void resetView();

    void loadEventData(int index);

    void getUserIndex();

    void loadUserAvailability();

    void loadAdminData();

    void loadAdminTasks();

    /*!
     * \brief session
     * \details Session passed between all classes to hold events.
     */
    Session *session;
private slots:

    /*!
     * \brief receiveshow
     * \details Function called when class receives signal to become visibale. Sets visiblity to true.
     */
    void receiveshow();

    /*!
     * \brief on_btnBack_clicked
     * \details Function called when Back button is clicked. Emits showEventPlanner()
     */
    void on_btnBack_clicked();

    void on_btnVolunteer_clicked();

    void on_btnAdminVolunteer_clicked();

    /*!
     * \brief on_wListEvents_clicked
     * \details Called when an Event in the Event list is clicked on. Fills TimeSlot list with time slots for the event where TimeSlot.isSelected() true.
     * \param index
     */
    void on_wListEvents_clicked(const QModelIndex &index);

    /*!
     * \brief on_addToTimeSlotButton_clicked
     * \details Called when Add Me to Time Slot button is clicked. Adds the current user (Session.getUser()) to the selected time slot.
     */
    void on_addToTimeSlotButton_clicked();

    void on_wListDates_clicked(const QModelIndex &index);

    void on_wListAdminDates_clicked(const QModelIndex &index);

    void on_wListAttendees_clicked(const QModelIndex &index);

    /*!
     * \brief updateDate
     * \details Update selected Date, auto-updating all which follows. (Event->[Date]->Timeslot->Attendees)
     * \param it - Iterator containing selected Event
     */
    void updateDate(bool mode);
    /*!
     * \brief updateAttendees
     * \details Update Attendees given a timeslot. (Event->Date->Timeslot->[Attendees])
     * \param it - Iterator containing the Attendees for the slot atSlot
     * \param atSlot - Slot to update the Attendees for
     */
    void updateAttendees(std::list<Event*>::iterator it, int atSlot);

    /*!
     * \brief updateTasksList
     * \details Update selected Timeslot. (Event->[Tasks])
     * \param it - Iterator containing selected Event
     */
    void updateTasksList();


signals:

    /*!
     * \brief showEventPlanner
     * \details Signal for switch back to the Event Planner
     */
    void showEventPlanner();


};
#endif // ADDINGMODE_H
