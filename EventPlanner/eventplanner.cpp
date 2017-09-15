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
    ui->label_2->setPixmap(food);
    ui->label_3->setPixmap(job);
    ui->label_4->setPixmap(note);
    ui->label_5->setPixmap(pokemon);
    ui->label_7->setPixmap(up);
    ui->label_2->setScaledContents(true);
    ui->label_3->setScaledContents(true);
    ui->label_4->setScaledContents(true);
    ui->label_5->setScaledContents(true);
    ui->label_7->setScaledContents(true);
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->label_7->show();
}

void EventPlanner::on_pushButton_clicked()
{
    this->hide();
    emit AddingModeshow();
}

void EventPlanner::on_pushButton_2_clicked()
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

void EventPlanner::on_pushButton_3_clicked()
{
    QMessageBox::about(this,"About us",tr("We are team J-Hawk!!\n"
                                          "\n"
                                       "Email: whatever@ku.edu\n"
                                          "\n"
                                       "Team members: Martin, Kevin, Jian, Simon\n"
                                          "\n"
                                       "This program was made with the Qt Creator IDE and Framework version 5.9.1 licensed under LGPL."));
}

void EventPlanner::on_pushButton_4_clicked()
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


