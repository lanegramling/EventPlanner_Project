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
     * \details Consturctor used to create fully initiallized Event object.
     * \param owner
     * \param eventName
     * \param month
     * \param day
     * \param year
     * \param timeSlots
     */
    Event(QString owner, QString eventName, int eventID, QStringList days, QList<int> timeslots);
    ~Event();

    /*!
     * \brief setDate
     * \param month
     * \details Sets private variable month to the passed integer.
     */
    void setDays(QString dayString);

    /*!
     * \brief getDay
     * \details Returns the date of the event
     * \return  QStringList of QString with format "MM-DD-YYYY"
     */
    QStringList getDays();

    QStringList getTasks();

    void setTasks(QString tasks);

    bool removeTask(QString task);


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

    QList<attendee*> getAttendees();

    QStringList getAttendeesAtTimeslot(int timeslot);

    void setAttendees(QList<attendee*>);

    void addAttendee(QString name, int slot);


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

    QStringList eventDays;

    QStringList eventTasks;

};

#endif // EVENT_H
