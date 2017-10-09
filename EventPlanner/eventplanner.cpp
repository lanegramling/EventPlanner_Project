#include "eventplanner.h"
#include "ui_eventplanner.h"


EventPlanner::EventPlanner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventPlanner)
{
    ui->setupUi(this);
    setWindowTitle("EventPlanner");
    setPicture();
}


EventPlanner::~EventPlanner()
{
    delete ui;
}

void EventPlanner::receiveShow() {
    this->show();
}

void EventPlanner::setPicture()
{
    QPixmap food(":/eventMainWindow/food.png"),
            job(":/eventMainWindow/job.png"),
            note(":/eventMainWindow/Note.png"),
            pokemon(":/eventMainWindow/Poke.png"),
            up(":/eventMainWindow/Up.png");
    ui->lblPicFood->setPixmap(food);
    ui->lblPicPerson->setPixmap(job);
    ui->lblPicNote->setPixmap(note);
    ui->lblPicPokemon->setPixmap(pokemon);
    ui->lblPicUpArrow->setPixmap(up);
    ui->lblPicFood->setScaledContents(true);
    ui->lblPicPerson->setScaledContents(true);
    ui->lblPicNote->setScaledContents(true);
    ui->lblPicPokemon->setScaledContents(true);
    ui->lblPicUpArrow->setScaledContents(true);
    ui->lblPicFood->show();
    ui->lblPicPerson->show();
    ui->lblPicNote->show();
    ui->lblPicPokemon->show();
    ui->lblPicUpArrow->show();
}

void EventPlanner::on_btnAddAvailabilityMode_clicked()
{
    this->hide();
    emit AddingModeshow();
}

void EventPlanner::on_btnEventAdminMode_clicked()
{
    this->hide();
    emit AdminModeshow();
}

void EventPlanner::getMode1()
{
    this->show();
}

void EventPlanner::getMode2()
{
    this->show();
}

void EventPlanner::on_btnAboutUs_clicked()
{
    QMessageBox::about(this,"About us",tr("We are team J-Hawk!!\n"
                                          "\n"
                                       "Email: whatever@ku.edu\n"
                                          "\n"
                                       "Team members: Martin, Kevin, Jian, Simon\n"
                                          "\n"
                                       "This program was made with the Qt Creator IDE and Framework version 4.X licensed under LGPL.\n"
                                          "\n"
                                          "\nModified October 2017 by Dustin Bingham, Lane Gramling, and Damian Vu."));
}

void EventPlanner::on_btnHelp_clicked()
{

    QMessageBox::about(this,"Help",tr("How to use EventPlanner:\n"
                                      "You can choose two different Modes by click their Button                                \n\n"
                                      "  A.In EventAdmin Mode:\n"
                                      "  ...You can add any event you want, but you have to have all the detail for your event.\n"
                                      "  ...The time slots do not have to be contiguous but must fall within the 24-hours of a given date.\n"
                                      "  ...An event can span multiple time slots (e.g. a two-hour event would occupy four time slots).\n"
                                      "  ...The date must be a real one (e.g. no February 30th).\n\n"
                                      "  B.In Adding Mode:\n"
                                      "  ...You can search by EventName or date or directly.\n"
                                      "  ...Clicking An Event, it will ask you 'Do you want it?'.\n"
                                      "  ...You can canncel an Event, click the canncel button."));
}

void EventPlanner::on_logoutButton_clicked() {
    this->hide();
    emit Logout();
}
