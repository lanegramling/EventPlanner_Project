#include "attendee.h"

attendee::attendee(){}

attendee::attendee(int id, QString aname, QList<int> avail) :
    eventID(id),
    name(name),
    availability(avail) {}

int attendee::getEventID() {
    return eventID;
}

void attendee::setEventID(int id) {
    eventID = id;
}

QString attendee::getAttendeeName() {
    return name;
}

void attendee::setAttendeeName(QString aname) {
    name = aname;
}

QList<int> attendee::getAvailability() {
    return availability;
}

void attendee::setAvailability(QList<int> avail) {
    availability = avail;
}

void attendee::addAvailability(int slot) {
    if (availability.indexOf(slot) == -1) availability.append(slot);
    qSort(availability);
}

QStringList attendee::getTasks() {
    return tasks;
}

void attendee::setTasks(QString taskString) {
    if (!taskString.isEmpty()) tasks = taskString.split(';');
}

void attendee::addTask(QString task) {
    tasks.append(task);
}
