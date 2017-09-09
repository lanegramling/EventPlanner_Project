#include "event.h"
#include <list>

Event::Event() {

}

Event::Event(QString owner, QString eventName, int month, int day, int* time) :
    Event::owner(owner),
    Event::month(month),
    Event::day(day),
    Event::eventName(eventName),
    Event::time(time)
    {Event::attendees << Event::owner;}

Event::~Event() {
    delete time;
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

QString Event::getOwner() const {
    return owner;
}

void Event::setOwner(QString owne) {
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
