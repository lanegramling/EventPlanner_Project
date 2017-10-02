#include "session.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Session::Session(){
}

Session::Session (QString user) : user(user){}

Session::~Session() {
    for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
        delete *it;
    }
}

void Session::addEvent(QString owner, QString eventName, int eventID, QString eventDate, QList<int> timeSlots, QList<attendee*> att) {
    Event* event = new Event(owner, eventName, eventID, eventDate, timeSlots);
    event->setAttendees(att);
    events.push_back(event);
}

bool Session::readEventsFromFile() {
    QFile inputFile("EventData.txt");

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       int counter = 0;
       int numEvents = in.readLine().toInt();

       while (counter < numEvents)
       {
               Event* event = new Event();
               event->setOwner(in.readLine());
               event->setEventName(in.readLine());
               int eid = in.readLine().toInt();
               event->setID(eid);
               event->setDate(in.readLine());
               event->setTimeSlots(helpermethods::listifyTimeslotInts(in.readLine()));

               // Attendees
               int numAttendees = in.readLine().toInt();
               QStringList listNames = in.readLine().split(',');

               QList<attendee*> temp = QList<attendee*>();
               for (int i = 0; i < numAttendees; i++) {
                    attendee* newAtt = new attendee();
                    newAtt->setEventID(eid);
                    newAtt->setAttendeeName(listNames[i]);
                    newAtt->setAvailability(helpermethods::listifyTimeslotInts(in.readLine()));
                    temp.append(newAtt);
               }

               event->setAttendees(temp);

               events.push_back(event);
               counter++;

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
        out << numberOfEvents() << "\n";
        for(std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
            out << (*it)->getOwner() << "\n";
            out << (*it)->getEventName() << "\n";
            out << (*it)->getID() << "\n";
            out << (*it)->getDate() << "\n";
            QString times = helpermethods::stringifyTimeslotInts((*it)->getTimeSlots());
            out << times << "\n";

            QList<attendee*> attn = (*it)->getAttendees();
            int numAttendees = attn.size();
            out << numAttendees << "\n";

            // Probably redo this later. Needs to work for now tho

            for (int i = 0; i < numAttendees; i++) {
                QString output = (i != numAttendees - 1) ? attn[i]->getAttendeeName() + "," : attn[i]->getAttendeeName() + "\n";
                out << output;
            }

            for (int i = 0; i < numAttendees; i++) {
                out << helpermethods::stringifyTimeslotInts(attn[i]->getAvailability()) << "\n";
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
