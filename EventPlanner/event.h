#ifndef EVENT_H
#define EVENT_H
#include <list>
#include <QString>
#include <QStringList>

class Event
{
public :
    Event();
    Event(QString owner, QString eventName, int month, int day, int year, int* time);
    ~Event();
    int getMonth() const;
    void setMonth(int month);
    int getDay() const;
    void setDay(int day);
    int getYear() const;
    void setYear(int year);
    QString getOwner() const;
    void setOwner(QString owne);
    QString getEventName();
    void setEventName(QString eventName);
    int* getTime() const;
    void setTime(int* time);
    QStringList getAttendees() const;
    void addAttendee(QString attendee);

private:
    QString owner;
    QString eventName;
    int month;
    int day;
    int year;
    int* time;
    QStringList attendees;
};

#endif // EVENT_H
