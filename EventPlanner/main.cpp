#include "eventplanner.h"
#include "eventadminmode.h"
#include "addingmode.h"
#include "session.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    Session session;
    session.readEventsFromFile();
    QApplication prog(argc, argv);
    QDesktopWidget* qDesk = QApplication::desktop();
    EventPlanner w;
    EventAdminMode mode1(&session);
    //QWidget *parent = 0;
    AddingMode mode2(&session);
    w.move((qDesk->width() - w.width())/2,(qDesk->height() - w.height())/2); // set window in the middle
    mode1.move((qDesk->width() - mode1.width())/2,(qDesk->height() - mode1.height())/2);// same
    mode2.move((qDesk->width() - mode2.width())/2,(qDesk->height() - mode2.height())/2);// same
    w.show();

    QObject::connect(&mode1,SIGNAL(showEventPlanner()),&w,SLOT(getMode1()));
    QObject::connect(&w,SIGNAL(AdminModeshow()),&mode1,SLOT(receiveshow()));

    QObject::connect(&mode2,SIGNAL(showEventPlanner()),&w,SLOT(getMode2()));//connect signal
    QObject::connect(&w,SIGNAL(AddingModeshow()),&mode2,SLOT(receiveshow()));//   with differen windows

    return (prog.exec());
}
