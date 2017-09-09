#ifndef EVENT_H
#define EVENT_H
#include <list>
#include <qstring>

class Event
{
public :
    Event(QString userName, int month, int day, QString eventName, int* time);
    ~Event();
    int getMonth() const;
    int getDay() const;
    QString getUserName() const;
    QString getEventName();
    int* getTime() const;
    std::list<QString> getAttendees() const;
    void addAttendee(QString attendee);

private:
    QString userName;
    QString eventName;
    int month;
    int day;
    int* time;
    std::list<QString> attendees;
};

#endif // EVENT_H
