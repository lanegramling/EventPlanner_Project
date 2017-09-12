#include "session.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>



Session::Session() {}

Session::Session (QString user) : user(user){}

Session::~Session() {

    for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
        delete *it;
    }
}

void Session::addEvent(QString owner, QString eventName, int month, int day, int year, QString startTime, QString endTime) {
    Event* event = new Event(owner, eventName, month, day, year, startTime, endTime);
    events.push_back(event);
}

bool Session::readEventsFromFile() {
    QFile inputFile("EventData.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int counter = 1;
       QStringList eventElements;
       eventElements.clear();
       while (!in.atEnd())
       {
               while(counter < 9){
                   QString line = in.readLine();
                   eventElements.push_back(line);
                   counter++;
               }

               Event* event = new Event();
               event->setOwner(eventElements.at(0));
               event->setEventName(eventElements.at(1));
               event->setMonth(eventElements.at(2).toInt());
               event->setDay(eventElements.at(3).toInt());
               event->setYear(eventElements.at(4).toInt());
               event->setStartTime(eventElements.at(5));
               event->setEndTime(eventElements.at(6));
               for (int i = 0; i < eventElements.at(7).size(); i++) {
                   QString attendee = "";
                   if  (eventElements.at(7).at(i) == '\"') {
                       for (int j = i + 1; j < eventElements.at(7).size(); j++) {
                           if (eventElements.at(7).at(j) != '\"') {
                               attendee.push_back(eventElements.at(7).at(j));
                           } else {
                               i = j + 1;
                               event->addAttendee(attendee);
                               break;
                           }
                       }
                   }
               }
               events.push_back(event);
               counter = 1;
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
            out << (*it)->getStartTime() << "\n";
            out << (*it)->getEndTime() << "\n";
            int size = (*it)->getAttendees().size();
            out << "(";
            for (int i = 0; i < size; i++) {
                if (i != size - 1) {
                    out << "\"" << (*it)->getAttendees().at(i) << "\", ";
                } else {
                    out << "\"" << (*it)->getAttendees().at(i) << "\")";
                }

            }
            out << "\n";
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
