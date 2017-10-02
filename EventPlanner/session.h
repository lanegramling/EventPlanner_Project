#ifndef SESSION_H
#define SESSION_H
#include <list>
#include <QString>
#include "event.h"
#include "attendee.h"
#include "helpermethods.h"

/*!
 * \brief The Session class
 * \details The session object is used to handle reading and writing events to file for storage as well as stroing events in memory while program is running.
 */
class Session {

public:

    /*!
     * \brief Session
     * \details Default constructor. All initializations are set to default.
     */
    Session();

    /*!
     * \brief Session
     * \details Constructor where private memebr variable QString user is set to the passed argument.
     * \param user
     */
    Session(QString user);

    ~Session();

    /*!
     * \brief addEvent
     * \details Creates a new Event using the passed arguments and pushes it to the end of private memeber variable td::list<Event*> events.
     * \param owner
     * \param eventName
     * \param month
     * \param day
     * \param year
     * \param timeSlots
     */
    void addEvent(QString owner, QString eventName, int eventID, QString eventDate, QList<int> timeSlots, QList<attendee*> att);

    /*!
     * \brief readEventsFromFile
     * \details Reads in contents of EventData.txt and parses for Event objects. Events objects are the pushed into std::list<Event*> events.
     * \return True if file succesfully parsed. False otherwise.
     */
    bool readEventsFromFile();

    /*!
     * \brief saveEventsToFile
     * \details Writes formatted contents of std::list<Event*> events to file EventData.txt.
     * \return True if file succesfully saved. False otherwise.
     */
    bool saveEventsToFile();

    /*!
     * \brief getUser
     * \details Returns the private member QString user.
     * \return QString
     */
    QString getUser() const;

    /*!
     * \brief setUser
     * \details Sets the private member variable QString user to the passed argument.
     * \param user
     */
    void setUser(QString user);

    /*!
     * \brief getEvents
     * \details Returns the private member variable std::list<Event*> events. This is a list of Event pointers of all Events avaivalbe in the Session.
     * \return std::list<Event*>
     */
    std::list<Event*>& getEvents();

    /*!
     * \brief numberOfEvents
     * \details Returns the size of std::list<Event*> events.
     * \return int
     */
    int numberOfEvents() const;

private:

    /*!
     * \brief events
     */
    std::list<Event*> events;

    /*!
     * \brief user
     */
    QString user;


};

#endif // SESSION_H
