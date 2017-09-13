#include "session.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>



Session::Session() {time = new int[48];}

Session::Session (QString user) : user(user){}

Session::~Session() {
     delete[] time;
    for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
        delete *it;
    }
}

void Session::addEvent(QString owner, QString eventName, int month, int day, int year, int* time) {
    Event* event = new Event(owner, eventName, month, day, year, time);
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
               while(counter < 8){
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
               int index = 0;
               for (int i = 0; i < eventElements.at(5).size(); i++) {
                   if (eventElements.at(5).at(i) == '1') {
                       time[index] = 1;
                       index++;
                   } else if (eventElements.at(5).at(i) == '0') {
                       time[index] = 0;
                       index++;
                   }
               }
               event->setTime(time);

               for (int i = 0; i < eventElements.at(6).size(); i++) {
                   QString attendee = "";
                   if  (eventElements.at(6).at(i) == '\"') {
                       for (int j = i + 1; j < eventElements.at(6).size(); j++) {
                           if (eventElements.at(6).at(j) != '\"') {
                               attendee.push_back(eventElements.at(6).at(j));
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
            out << "[";
            for(int i = 0; i < 48; i++) {
                if (i != 47) {

                    out << ((*it)->getTime())[i] << ", ";
                } else {
                    out << ((*it)->getTime())[i] << "]\n";
                }
            }
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
