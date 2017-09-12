#ifndef EVENT_H
#define EVENT_H
#include <list>
#include <QString>
#include <QStringList>

class Event
{
public :
    Event();
    Event(QString owner, QString eventName, int month, int day, int year, QString startTime, QString endTime);
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
    QString getStartTime() const;
    void setStartTime(QString startTime);
    QString getEndTime() const;
    void setEndTime(QString endTime);
    QStringList getAttendees() const;
    void addAttendee(QString attendee);

private:
    QString owner;
    QString eventName;
    int month;
    int day;
    int year;
    QString startTime;
    QString endTime;
    QStringList attendees;

};

#endif // EVENT_H
