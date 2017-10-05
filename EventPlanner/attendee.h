#ifndef ATTENDEE_H
#define ATTENDEE_H

#include <QString>
#include <QList>


class attendee
{
public:
    /*!
     * \brief Default constructor
     */
    attendee();

    attendee(int id, QString aname, QList<int> avail);

    /*!
     * \brief getEventID
     * \return int ID of event
     */
    int getEventID();

    /*!
     * \brief setEventID
     * \param id of event
     */
    void setEventID(int id);

    /*!
     * \brief getAttendeeName
     * \return QString attendee name
     */
    QString getAttendeeName();

    /*!
     * \brief setAttendeeName
     * \param name of event
     */
    void setAttendeeName(QString aname);

    /*!
     * \brief getAvailability
     * \return List of ints with user availability
     */
    QList<int> getAvailability();

    /*!
     * \brief setAvailability
     * \param avail of user for event id
     */
    void setAvailability(QList<int> avail);

    void addAvailability(int slot);

    QStringList getTasks();

    void setTasks(QString taskString);

    void addTask(QString task);

private:
    int eventID;
    QString name;
    QList<int> availability;
    QStringList tasks;
};

#endif // ATTENDEE_H
