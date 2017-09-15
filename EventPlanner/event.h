#ifndef EVENT_H
#define EVENT_H
#include "timeslot.h"
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
    Event(QString owner, QString eventName, int month, int day, int year, QList<TimeSlot> timeSlots);
    ~Event();
    /*!
     * \brief getMonth
     * \details Returns the month that the event will occur.
     * \return Integer
     */
    int getMonth() const;

    /*!
     * \brief setMonth
     * \param month
     * \details Sets private variable month to the passed integer.
     */
    void setMonth(int month);

    /*!
     * \brief getDay
     * \details Returns the day of the month that the event will occur.
     * \return  Integer
     */
    int getDay() const;

    /*!
     * \brief setDay
     * \param day
     * \details Sets private variable day to the passed integer.
     */
    void setDay(int day);

    /*!
     * \brief getYear
     * \details Returns the year that the event will occur.
     * \return  Integer
     */
    int getYear() const;

    /*!
     * \brief setYear
     * \param year
     * \details Sets private variable year to the passed integer.
     */
    void setYear(int year);

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
    QList<TimeSlot> getTimeSlots();

    /*!
     * \brief setTimeSlots
     * \details Sets private variable timeSlots to the passed QList<TimeSlot>.
     * \param timeSlots
     */
    void setTimeSlots(QList<TimeSlot> timeSlots);

    /*!
     * \brief printEvent
     * \details A formatted QString with the Owner, Event Name, and Date
     * \return QString
     */
    QString printEvent();

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
     * \brief month
     */
    int month;
    /*!
     * \brief day
     */
    int day;
    /*!
     * \brief year
     */
    int year;
    /*!
     * \brief timeSlots
     */
    QList<TimeSlot> timeSlots;

};

#endif // EVENT_H
