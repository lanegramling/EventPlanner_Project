#include "event.h"
#include <list>

Event::Event(QString userName, int month, int day, QString eventName, int* time) {
    Event::userName = userName;
    Event::month = month;
    Event::day = day;
    Event::eventName = eventName;
    Event::time = time;
}

Event::~Event() {
    delete time;
}

int Event::getMonth() const {
    return month;
}

int Event::getDay() const {
    return day;
}

QString Event::getUserName() const {
    return userName;
}
QString Event::getEventName() {
    return eventName;
}
int* Event::getTime() const {
    return time;
}
std::list<QString> Event::getAttendees() const {
    return attendees;
}

void Event::addAttendee(QString attendee) {
    attendees.push_back(attendee);
}
