#include "event.h"
#include <list>

Event::Event() {

}

Event::Event(QString owner, QString eventName, int month, int day, int year, QList<TimeSlot> timeSlots) :
    owner(owner),
    eventName(eventName),
    month(month),
    day(day),
    year(year),
    timeSlots(timeSlots)
    {

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

QList<TimeSlot> Event::getTimeSlots() {
    return timeSlots;
}

void Event::setTimeSlots(QList<TimeSlot> timeSlots) {
    Event::timeSlots = timeSlots;
}
