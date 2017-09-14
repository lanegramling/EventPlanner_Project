#ifndef TIMESLOT_H
#define TIMESLOT_H
#include <QStringList>
#define TIME_SLOTS_LENGTH 48

/*!
 * \brief The TimeSlot class
 * \details Class using to hold information for a single time slot of an event.
 */
class TimeSlot
{
public:
    /*!
     * \brief TimeSlot
     * \details Default constructor. Privare bool selected is initialized to false.
     */
    TimeSlot();

    ~TimeSlot();

    /*!
     * \brief addAttendee
     * \details Pushes passed QString onto private membervariable QStringList attendees.
     * \param attendee
     */
    void addAttendee(QString attendee);

    /*!
     * \brief getAttendees
     * \details Returns the private membervariable QStringList attendees.
     * \return QStringList
     */
    QStringList getAttendees() const;

    /*!
     * \brief getTime12Hour
     * \details Returns the QString that contains the 12 hour clock format of the time slot.
     * \return QString
     */
    QString getTime12Hour() const;

    /*!
     * \brief setTime12Hour
     * \details The private memebr variable QString displayTime12Hour is set to the passed QString.
     * \param time
     */
    void setTime12Hour(QString time);

    /*!
     * \brief getTime24Hour
     * \details Returns the QString that contains the 24 hour clock format of the time slot.
     * \return QString
     */
    QString getTime24Hour() const;

    /*!
     * \brief setTime24Hour
     * \details The private memebr variable QString displayTime24Hour is set to the passed QString.
     * \param time
     */
    void setTime24Hour(QString time);

    /*!
     * \brief isSelected
     * \details Returns a bool that represents if the TimeSlot has been selected to be part of the Event.
     * \return bool
     */
    bool isSelected() const;

    /*!
     * \brief setTrue
     * \details Set the private member variable bool selected to true.
     */
    void setTrue();

    /*!
     * \brief setFalse
     * \details Set the private member variable bool selected to false.
     */
    void setFalse();

    /*!
     * \brief clearTimeSlot
     * \details QStringList attendees is cleared of all QStrings and bool selected is set to false.
     */
    void clearTimeSlot();

    /*!
     * \brief setAttendees
     * \details The private member variable QStringList attendees is set to the passed argument.
     * \param attendees
     */
    void setAttendees(QStringList attendees);

private:
    QStringList attendees;
    QString displayTime12Hour;
    QString displayTime24Hour;
    bool selected;
};

#endif // TIMESLOTS_H
