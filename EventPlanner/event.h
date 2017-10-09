#ifndef EVENT_H
#define EVENT_H
#include "attendee.h"
#include <list>
#include <QString>
#include <QStringList>

/*!
 * \brief The Event class
 * \details Class used to store details of an event.
 */
class Event
{
public :
    /*!
     * \brief Event
     * \details Default constructor. Only default initilizations are made.
     */
    Event();

    /*!
     * \brief Event
     * \details Constructor used to create fully initialized Event object.
     * \param owner Name of the creator
     * \param eventName Name of the event
     * \param eventID Event's ID
     * \param days List of days of format 'MM-DD-YYYY' that it spans
     * \param tasks List of tasks that have not been fulfilled
     * \param timeslots List of timeslots that range from 0 - ((number of days * 48) - 1)
     */
    Event(QString owner, QString eventName, int eventID, QStringList days, QStringList tasks, QList<int> timeslots);
    ~Event();


    /*!
     * \brief setDays
     * \param dayString
     * \details Takes list of comma separated days of format 'MM-DD-YYYY' and separates it into a list
     */
    void setDays(QString dayString);

    /*!
     * \brief getDay
     * \details Returns the date of the event
     * \return  QStringList of QString with format "MM-DD-YYYY"
     */
    QStringList getDays();


    /*!
     * \brief setTasks
     * \details Takes a list of semi-colon separated strings and splits it into a list
     * \param tasks
     */
    void setTasks(QString tasks);


    /*!
     * \brief getTasks
     * \return QStringList of tasks
     */
    QStringList getTasks();

    /*!
     * \brief removeTask
     * \param task to be removed
     * \return true if the task was successfully removed
     */
    bool removeTask(QString task);

    /*!
     * \brief getEventName
     * \details Returns the name of the event.
     * \return QString
     */
    QString getEventName();

    /*!
     * \brief setEventName
     * \details Sets private variable eventName to the passed QString.
     * \param eventName
     */
    void setEventName(QString eventName);

    /*!
     * \brief getOwner
     * \details Returns the name of the person who created the event.
     * \return QString
     */
    QString getOwner() const;

    /*!
     * \brief setOwner
     * \details Sets private variable owner to the passed QString.
     * \param owner
     */
    void setOwner(QString owner);

    /*!
     * \brief getTimeSlots
     * \details Returns the private member QList<TimeSlot> timeSlots.
     * \return QList<TimeSlot>
     */
    QList<int> getTimeSlots();

    /*!
     * \brief setTimeSlots
     * \details Sets private variable timeSlots to the passed QList<TimeSlot>.
     * \param timeSlots
     */
    void setTimeSlots(QList<int> timeSlots);

    /*!
     * \brief printEvent
     * \details A formatted QString with the Owner, Event Name, and Date
     * \return QString
     */
    QString printEvent();

    /*!
     * \brief getID
     * \return int EventID
     */
    int getID() const;
    /*!
     * \brief setID
     * \param ID Event ID
     */
    void setID(int ID);

    /*!
     * \brief getAttendees
     * \return
     */
    QList<attendee*> getAttendees();
    /*!
     * \brief getAttendeesAtTimeslot
     * \param timeslot
     * \return
     */
    QStringList getAttendeesAtTimeslot(int timeslot);
    /*!
     * \brief setAttendees
     */
    void setAttendees(QList<attendee*>);
    /*!
     * \brief addAttendee
     * \param name
     * \param slot
     */
    void addAttendee(QString name, int slot);
    /*!
     * \brief addAttendee
     * \param attn
     */
    void addAttendee(attendee* attn);

    /*!
     * \brief addAttendee
     * \param name
     * \param slots
     */
    void addAttendee(QString name, QList<int> slot);

    /*!
     * \brief hasAttendee
     * \param name
     * \return -1 if no attendee has matching name, otherwise returns the index of the attendee
     */
    int hasAttendee(QString name);




private:

    QString owner;
    QString eventName;

    int eventID;

    QList<int> timeslots;
    QList<attendee*> attendees;


    QStringList eventDays;
    QStringList eventTasks;

};

#endif // EVENT_H
