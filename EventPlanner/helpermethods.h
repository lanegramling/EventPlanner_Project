#ifndef HELPERMETHODS_H
#define HELPERMETHODS_H

#include <QList>
#include <QString>
#include <QVariant>

class helpermethods
{
public:

    /*!
     * \brief toTime Will give specific time for given timeslot int
     *        e.g. 12|24h: 27 = 1:30pm|13:30
     * \param timeslot 0-47
     * \param format TRUE: 24h format | FALSE: 12h format
     * \return QString Time in 12h/24h format
     */
    static QString toTime(int timeslot, bool format);

    /*!
     * \brief toTimeSlot Will utilize toTime to create 30min timeslot string
     *        e.g. Timeslot-Timeslot+1: 27 = 1:30pm-2:00pm|13:30-14:00
     * \param timeslot 0-47
     * \param format TRUE: 24h format | FALSE: 12h format
     * \return
     */
    static QString toTimeSlot(int timeslot, bool format);

    /*!
     * \brief getTimeString Returns a smarter timeslot string based on contiguous timeslots
     * \param timeslots Will sort then utilize list of ints with range 0-47
     * \param format TRUE: 24h format | FALSE: 12h format
     * \return
     */
    static QString getTimeString(QList<int> timeslots, bool format);

    /*!
     * \brief stringifyTimeslotInts Inverse function of listifyTimeslotInts
     * \param timeslots QList<int>
     * \return QString of timeslots e.g. "0,1,2,3,4"
     */
    static QString stringifyTimeslotInts(QList<int> timeslots);

    /*!
     * \brief listifyTimeslotInts Inverse function of stringifyTimeslotInts
     * \param timeslotString e.g. "0,1,2,3,4"
     * \return QList of timeslots
     */
    static QList<int> listifyTimeslotInts(QString timeslotString);

private:
    /*!
     * \brief helpermethods Private constructor so helpermethods is never initialized.
     */
    helpermethods();
};

#endif // HELPERMETHODS_H
