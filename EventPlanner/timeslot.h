#ifndef TIMESLOT_H
#define TIMESLOT_H
#include <QStringList>
#define TIME_SLOTS_LENGTH 48


class TimeSlot
{
public:
    TimeSlot();
    ~TimeSlot();
    void addAttendee(QString Attendee);
    QStringList getAttendees() const;
    QString getTime12Hour() const;
    void setTime12Hour(QString time);
    QString getTime24Hour() const;
    void setTime24Hour(QString time);
    bool isSelected() const;
    void setTrue();
    void setFalse();
    void clearTimeSlot();
    void setAttendees(QStringList attendees);

private:
    QStringList attendees;
    QString displayTime12Hour;
    QString displayTime24Hour;
    bool selected;
};

#endif // TIMESLOTS_H
