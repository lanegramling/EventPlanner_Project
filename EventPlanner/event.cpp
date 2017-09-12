#include "event.h"
#include <list>

Event::Event() {

}

Event::Event(QString owner, QString eventName, int month, int day, int year, QString startTime, QString endTime) :
    owner(owner),
    eventName(eventName),
    month(month),
    day(day),
    year(year),
    startTime(startTime),
    endTime(endTime)
    {
        Event::attendees << Event::owner;
    }

Event::~Event() {
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

QString Event::getStartTime() const {
    return startTime;
}

void Event::setStartTime(QString startTime) {
    Event::startTime = startTime;
}

QString Event::getEndTime() const {
    return endTime;
}

void Event::setEndTime(QString endTime) {
    Event::endTime = endTime;
}

QStringList Event::getAttendees() const {
    return attendees;
}

void Event::addAttendee(QString attendee) {
    attendees << attendee;
}
