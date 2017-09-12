#include "event.h"
#include <list>

Event::Event() {

}

Event::Event(QString owner, QString eventName, int month, int day, int year, int* time) :
    owner(owner),
    eventName(eventName),
    month(month),
    day(day),
    year(year)
    {Event::time = new int[48];
     for(int i = 0; i < 48;i++)
     {Event::time[i] = time[i];}
    Event::attendees << Event::owner;}

Event::~Event() {
    delete[] time;
}

int Event::getMonth() const {
    return month;
}

void Event::setMonth(int month) {
    Event::month = month;
}

int Event::getDay() const {
    return day;
}

void Event::setDay(int day) {
    Event::day = day;
}

int Event::getYear() const {
    return year;
}

void Event::setYear(int year) {
    Event::year = year;
}

QString Event::getOwner() const {
    return owner;
}

void Event::setOwner(QString owner) {
    Event::owner = owner;
}

QString Event::getEventName() {
    return eventName;
}

void Event::setEventName(QString eventName) {
    Event::eventName = eventName;
}

int* Event::getTime() const {
    return time;
}

void Event::setTime(int* time) {
    Event::time = time;
}

QStringList Event::getAttendees() const {
    return attendees;
}

void Event::addAttendee(QString attendee) {
    attendees << attendee;
}
