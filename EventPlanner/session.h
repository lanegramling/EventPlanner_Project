#ifndef SESSION_H
#define SESSION_H
#include <list>
#include <QString>

#include "event.h"

class Session {

public:

    Session();
    Session(QString user);
    ~Session();
    void addEvent(QString owner, QString eventName, int month, int day, int* time);
    bool readEventsFromFile();
    bool saveEventsToFile();
    QString getUser() const;
    void setUser(QString user);
    std::list<Event*>& getEvents();
    int numberOfEvents() const;

private:

    std::list<Event*> events;
    QString user;
};

#endif // SESSION_H
