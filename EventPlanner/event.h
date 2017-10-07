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
     *
     * \param owner
     * \param eventName
     *
     * \param month
     * \param day
     * \param year
     *
     * \param tasks
     *
     * \param timeslots
     */
    Event(QString owner, QString eventName, int eventID, QStringList days, QStringList tasks, QList<int> timeslots);
    ~Event();


    /*!
     * \brief setDay
     * \param day
     * \details Sets private variable month to the passed integer.
     */
    void setDays(QString dayString);

    /*!
     * \brief getDay
     * \details Returns the date of the event
     * \return  QStringList of QString with format "MM-DD-YYYY"
     */
    QStringList getDays();


    //Tasks
    /*!
     * \brief setTasks
     * \details
     * \return
     */
    void setTasks(QString tasks);


    /*!
     * \brief getTasks
     * \return
     */
    QStringList getTasks();
    bool removeTask(QString task);


    //Event Name
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


    //Owner
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

    //Timeslots
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

    //Print Event
    /*!
     * \brief printEvent
     * \details A formatted QString with the Owner, Event Name, and Date
     * \return QString
     */
    QString printEvent();

    //ID
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


    //Atttendees
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
     * \brief hasAttendee
     * \param name
     * \return -1 if no attendee has matching name, otherwise returns the index of the attendee
     */
    int hasAttendee(QString name);




private:
    /*!
     * \brief owner
     */
    QString owner;

    /*!
     * \brief eventName
     */
    QString eventName;

    /*!
     * \brief eventID
     */
    int eventID;

    /*!
     * \brief timeSlots
     */
    QList<int> timeslots;

    /*!
     * \brief attendees
     */
    QList<attendee*> attendees;

    /*!
     * \brief eventDays
     */
    QStringList eventDays;

    /*!
     * \brief eventTasks
     */
    QStringList eventTasks;

};

#endif // EVENT_H
