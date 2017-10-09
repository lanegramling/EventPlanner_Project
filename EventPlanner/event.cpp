#include "event.h"
#include <list>

Event::Event() {}

Event::Event(QString owner, QString eventName, int eventID, QStringList days, QStringList tasks, QList<int> timeslots) :

    owner(owner),
    eventName(eventName),
    eventID(eventID),
    eventDays(days),
    eventTasks(tasks),
    timeslots(timeslots)
    {}

Event::~Event() {
    if (attendees.length() > 0) {
        foreach (attendee* a, attendees) {
            delete a;
        }
    }
}

QStringList Event::getDays() {
    return eventDays;
}

void Event::setDays(QString dayString) {
    eventDays = dayString.split(',');
}

QStringList Event::getTasks() {
    return eventTasks;
}

void Event::setTasks(QString tasks) {
    if (!tasks.isEmpty()) eventTasks = tasks.split(';');
}

bool Event::removeTask(QString task) {
    return (eventTasks.removeOne(task));
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

QList<int> Event::getTimeSlots() {
    return timeslots;
}

void Event::setTimeSlots(QList<int> timeSlots) {
    timeslots = timeSlots;
}

QString Event::printEvent() {
    return eventName + " : Created by " + owner;
}

int Event::getID() const {
    return eventID;
}

void Event::setID(int ID) {
    eventID = ID;
}

QList<attendee*> Event::getAttendees() {
    return attendees;
}

QStringList Event::getAttendeesAtTimeslot(int timeslot) {
    attendee* a;
    QStringList names;
    foreach (a, attendees) {
        if (a->getAvailability().indexOf(timeslot) != -1) names.append(a->getAttendeeName());
    }
    return names;
}

void Event::setAttendees(QList<attendee*> aList) {
    attendees = aList;
}

void Event::addAttendee(QString name, int slot) {
    int index = hasAttendee(name);
    if (index == -1) {
        attendee* att = new attendee();
        att->setAttendeeName(name);
        att->addAvailability(slot);
        att->setEventID(eventID);
        attendees.append(att);
    } else {
        attendees[index]->addAvailability(slot);
    }
}

void Event::addAttendee(QString name, QList<int> slot) {
    int index = hasAttendee(name);
    if (index == -1) {
        attendee* att = new attendee();
        att->setAttendeeName(name);
        att->setAvailability(slot);
        att->setEventID(eventID);
        attendees.append(att);
    } else {
        foreach(int timeslot, slot) {
            attendees[index]->addAvailability(timeslot);
        }
    }
}

void Event::addAttendee(attendee *attn) {
    attendees.append(attn);
}

int Event::hasAttendee(QString name) {
    int numAttendees = attendees.size();
    for (int i = 0; i < numAttendees; i++) {
        if (attendees[i]->getAttendeeName() == name) return i;
    }
    return -1;
}
