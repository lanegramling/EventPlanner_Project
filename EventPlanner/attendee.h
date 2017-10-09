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

    /*!
     * \brief Constructor
     * \details Will create a full attendee object with an eventid, name, and list of availability
     * \param id
     * \param aname
     * \param avail
     */
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

    /*!
     * \brief addAvailability
     * \param slot to add to availability list
     */
    void addAvailability(int slot);

    /*!
     * \brief getTasks
     * \return  QStringList of tasks
     */
    QStringList getTasks();

    /*!
     * \brief setTasks
     * \param taskString String of semi-colon separated task strings
     */
    void setTasks(QString taskString);

    /*!
     * \brief addTask
     * \details Adds a QString task to the list of tasks
     * \param task
     */
    void addTask(QString task);

private:
    int eventID;
    QString name;
    QList<int> availability;
    QStringList tasks;
};

#endif // ATTENDEE_H
