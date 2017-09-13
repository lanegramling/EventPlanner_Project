#include "session.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Session::Session (QString user) : user(user){}

Session::~Session() {
     delete[] time;
    for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
        delete *it;
    }
}

void Session::addEvent(QString owner, QString eventName, int month, int day, int year, QList<TimeSlot> timeSlots) {
    Event* event = new Event(owner, eventName, month, day, year, timeSlots);
    events.push_back(event);
}

bool Session::readEventsFromFile() {
    QFile inputFile("EventData.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int counter = 0;
       QStringList eventElements;
       eventElements.clear();
       while (!in.atEnd())
       {
               while(counter < 197){
                   QString line = in.readLine();
                   eventElements.push_back(line);
                   counter++;
               }

               Event* event = new Event();
               int index = 0;
               event->setOwner(eventElements.at(index)); index++;
               event->setEventName(eventElements.at(index)); index++;
               event->setMonth(eventElements.at(index).toInt());index++;
               event->setDay(eventElements.at(index).toInt()); index++;
               event->setYear(eventElements.at(index).toInt()); index++;
               QList<TimeSlot> timeSlots;
               for (int i = 0; i < TIME_SLOTS_LENGTH; i++) {
                   TimeSlot tempTimeSlot;
                   if (eventElements.at(index).toInt() == 1) {
                       tempTimeSlot.setTrue();
                   } else {
                       tempTimeSlot.setFalse();
                   }
                   index++;
                   tempTimeSlot.setTime12Hour(eventElements.at(index)); index++;
                   tempTimeSlot.setTime24Hour(eventElements.at(index)); index++;
                   for (int j = 0; j < eventElements.at(index).size(); j ++) {
                       if (eventElements.at(index).at(j) == '"') {
                           QString attendee = "";
                           for (int l = j+1 ; l < eventElements.at(index).size(); l ++) {
                               if (eventElements.at(index).at(l) != '"') {
                                   attendee.push_back(eventElements.at(index).at(l));
                               } else {
                                   j = l;
                                   break;
                               }
                           }
                           tempTimeSlot.addAttendee(attendee);
                       }
                   }
                   timeSlots.push_back(tempTimeSlot);
               }
               event->setTimeSlots(timeSlots);

               events.push_back(event);
               counter = 0;
               eventElements.clear();

       }
       inputFile.close();
       return true;
    } else {
        return false;
    }
}

bool Session::saveEventsToFile() {

    QFile file("EventData.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        return false;
    } else {
        QTextStream out(&file);
        for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
            out << (*it)->getOwner() << "\n";
            out << (*it)->getEventName() << "\n";
            out << (*it)->getMonth() << "\n";
            out << (*it)->getDay() << "\n";
            out << (*it)->getYear() << "\n";
            for (int i = 0; i < (*it)->getTimeSlots().size(); i++) {
                if ((*it)->getTimeSlots().at(i).isSelected()) {
                    out << "1\n";
                } else {
                    out << "0\n";
                }
                out << (*it)->getTimeSlots().at(i).getTime12Hour() << "\n";
                out << (*it)->getTimeSlots().at(i).getTime24Hour() << "\n";
                for (int j = 0; j < (*it)->getTimeSlots().at(i).getAttendees().size(); j++) {
                    out << "\"" << (*it)->getTimeSlots().at(i).getAttendees().at(j) << "\" ";
                }
                out << "\n";
            }
        }
        file.close();
        return true;
    }
}

QString Session::getUser() const {
    return user;
}

void Session::setUser(QString user) {
    Session::user = user;

}

std::list<Event*>& Session::getEvents() {
    return events;
}

int Session::numberOfEvents() const{
    return (int) events.size();
}
