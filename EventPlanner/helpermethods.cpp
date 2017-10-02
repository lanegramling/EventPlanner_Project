#include "helpermethods.h"

helpermethods::helpermethods()
{

}

QString helpermethods::toTime(int timeslot, bool format) {
    int hour;
    QString min;

    if (format) {
        hour = timeslot / 2;
    } else {
        hour = (timeslot % 24) / 2;
        if (hour == 0) hour = 12;
    }

    min = ((timeslot % 2) == 0) ? "00" : "30";

    QString time = QVariant(hour).toString() + ":" + min;

    if (format && hour < 10) time = "0" + time;

    if (!format) time = (timeslot < 24) ? time + "am" : time + "pm";

    return time;

}

QString helpermethods::toTimeSlot(int timeslot, bool format) {
    QString result = toTime(timeslot, format) + "-" + toTime(timeslot + 1, format);

    return result;
}

QString helpermethods::getTimeString(QList<int> timeslots, bool format) {
    qSort(timeslots.begin(), timeslots.end()); // Sort list of timeslots

    QString timestring = "";

    int prevTime = -1;
    int workingTimeslot = -1;
    int slot;

    foreach(slot, timeslots) {
        if (workingTimeslot == -1) {
            workingTimeslot = slot;
        } else if (slot != prevTime + 1) {
            timestring = timestring + toTimeSlot(workingTimeslot, format) + ", ";
            workingTimeslot = slot;
        }
        prevTime = slot;
    }

    if (workingTimeslot != -1) {
        timestring = timestring + toTime(workingTimeslot, format) + "-" + toTime((prevTime + 1) % 48, format);
    }

    if (workingTimeslot == 0 && prevTime == 47) timestring = "ALL DAY LONG";

    if (timestring.isEmpty()) timestring = "NOT AVAILABLE AT ALL";

    return timestring;
}

QString helpermethods::stringifyTimeslotInts(QList<int> timeslots) {
    QString stringList = "";
    int slot;
    foreach(slot, timeslots) {
        stringList += (timeslots.indexOf(slot) != (timeslots.size() - 1)) ? (slot + ",") : slot;
    }
    return stringList;
}

QList<int> helpermethods::listifyTimeslotInts(QString timeslotString) {
    QStringList temp = timeslotString.split(',');

    QString s;

    QList<int> final = QList<int>();

    foreach(s, temp) {
        final.append(s.toInt());
    }

    return final;
}
