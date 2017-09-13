#ifndef EVENT_H
#define EVENT_H
#include "timeslot.h"
#include <list>
#include <QString>
#include <QStringList>

class Event
{
public :
    Event();
    Event(QString owner, QString eventName, int month, int day, int year, QList<TimeSlot> timeSlots);
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
    QList<TimeSlot> getTimeSlots();
    void setTimeSlots(QList<TimeSlot> timeSlots);

private:
    QString owner;
    QString eventName;
    int month;
    int day;
    int year;
    QList<TimeSlot> timeSlots;

};

#endif // EVENT_H
