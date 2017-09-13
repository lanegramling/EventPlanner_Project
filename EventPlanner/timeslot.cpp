#include "timeslot.h"

TimeSlot::TimeSlot() {
    selected = false;
}

TimeSlot::~TimeSlot() {
    attendees.clear();
}

void TimeSlot::addAttendee(QString attendee) {
    attendees.push_back(attendee);
}

QStringList TimeSlot::getAttendees() const {
    return attendees;
}
QString TimeSlot::getTime12Hour() const {
    return displayTime12Hour;
}

void TimeSlot::setTime12Hour(QString time) {
    displayTime12Hour = time;
}

QString TimeSlot::getTime24Hour() const {
    return displayTime24Hour;
}

void TimeSlot::setTime24Hour(QString time) {
    displayTime24Hour = time;
}

bool TimeSlot::isSelected() const {
    return selected;
}

void TimeSlot::setTrue() {
    selected = true;
}

void TimeSlot::setFalse() {
    selected = false;
}

void TimeSlot::clearTimeSlot() {
    attendees.clear();
    selected = false;
}

void TimeSlot::setAttendees(QStringList attendees) {
    TimeSlot::attendees = attendees;
}
