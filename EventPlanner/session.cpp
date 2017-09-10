#include "session.h"
#include <QFile>
#include <QTextStream>



Session::Session() {}

Session::Session (QString user) : user(user){}

Session::~Session() {

    for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
        delete *it;
    }
}

void Session::addEvent(QString owner, QString eventName, int month, int day, int* time) {
    Event* event = new Event(owner, eventName, month, day, time);
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
           if (counter == 7) {
               Event* event = new Event();
               event->setOwner(eventElements.at(0));
               event->setEventName(eventElements.at(1));
               event->setMonth(eventElements.at(2).toInt());
               event->setDay(eventElements.at(3).toInt());

               int* time = new int[48];
               int index = 0;
               for (int i = 0; i < eventElements.at(4).size(); i++) {
                   if (eventElements.at(4).at(i) == '1') {
                       time[index] = 1;
                       index++;
                   } else if (eventElements.at(4).at(i) == '0') {
                       time[index] = 0;
                       index++;
                   }
               }
               event->setTime(time);

               for (int i = 0; i < eventElements.at(5).size(); i++) {
                   QString attendee = "";
                   if  (eventElements.at(5).at(i) == '\"') {
                       for (int j = i + 1; j < eventElements.at(5).size(); j++) {
                           if (eventElements.at(5).at(j) != '\"') {
                               attendee.push_back(eventElements.at(5).at(j));
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
           } else {
               QString line = in.readLine();
               eventElements.push_back(line);
               counter++;
           }
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
        return true;
    }
}

QString Session::getUser() const {
    return user;
}

void Session::setUser(QString user) {

}

std::list<Event*> Session::getEvents() {
    return events;
}
