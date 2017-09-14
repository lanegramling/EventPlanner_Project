#include "addingmode.h"
#include "ui_addingmode.h"
#include "eventplanner.h"
#include <QString>
#include <QList>

AddingMode::AddingMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddingMode),
    session(session)
{
    ui->setupUi(this);
    setWindowTitle("Adding Mode");
    ui->listWidget->clear();
    EventIndex = 0;
    person_name = "";
    int number = 1;
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
        ui->listWidget->addItem(QString::number(number)+". "+(*it)->getEventName());
        number++;
    }
}
AddingMode::~AddingMode()
{
    delete ui;
}

void AddingMode::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    ui->lineEdit_2->setText("");
    ui->lineEdit->setText("");
    this->hide();
    person_name = "";
    EventName = "";
    emit showEventPlanner();
}

void AddingMode::receiveshow()
{
    if (ui->listWidget->count() != session->numberOfEvents()) {
        ui->listWidget->clear();
        int number = 1;
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
           ui->listWidget->addItem(QString::number(number)+". " + (*it)->getEventName());
        number++;
        }}
        else{
            for(int i = 0; i < ui->listWidget->count(); i++)
            {ui->listWidget->item(i)->setHidden(false);}
        }
    this->show();
}

void AddingMode::on_lineEdit_textChanged(const QString &arg1)
{
    EventName = arg1; // get input
}

void AddingMode::on_pushButton_clicked()
{
    //search name
    int i=0;

    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
    {
       if(EventName != (*it)->getEventName())
        {
            ui->listWidget->item(i)->setHidden(true);
            session->setUser(person_name);
        }
        i++;
     }

}

void AddingMode::on_pushButton_3_clicked()
{
    //search free days
}

void AddingMode::on_spinBox_valueChanged(int arg1)
{ // (if)-(else if)-(else) use to check "fake date .e.g: Feb 30, Nov 66"
    if((arg1 == 4)||(arg1 == 6)||(arg1 == 9)||(arg1 == 11))
    {ui->spinBox_2->setMaximum(30);}
    else if(arg1 == 2)
    {ui->spinBox_2->setMaximum(28);}
    else
    {ui->spinBox_2->setMaximum(31);}
    month = arg1;
}

void AddingMode::on_spinBox_2_valueChanged(int arg1)
{day = arg1;}

void AddingMode::on_spinBox_3_valueChanged(int arg1)
{year = arg1;}

void AddingMode::on_listWidget_doubleClicked(const QModelIndex &index)
{
    ui->listWidget_2->clear();
    int count =0;
    EventIndex = index.row();
    for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it) {
       if(count == EventIndex)
       {
           for (int i = 0; i <  (*it)->getTimeSlots().length(); i++) {
                  if(((*it)->getTimeSlots()).at(i).isSelected())
                    { ui->listWidget_2->addItem(((*it)->getTimeSlots()).at(i).getTime12Hour());}
           }
           break;}
       count++;
    }

}

void AddingMode::on_lineEdit_2_textChanged(const QString &arg1)
{
    person_name = arg1;
}

void AddingMode::on_listWidget_2_doubleClicked(const QModelIndex &index)
{
    int index_of_list = 0;
    index_of_list = index.row();
    if(person_name == "")
    {QMessageBox::warning(this,"Warning!!","Please Enter your name on the top-left line");}
    else{
        int count = 0;
switch(QMessageBox::question(this,"Adding","Do you want to join it?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
    case QMessageBox::Ok:
        for(std::list<Event*>::iterator it = (session->getEvents()).begin(); it != (session->getEvents()).end(); ++it)
        {
         if(count == EventIndex)
         {
             QList<TimeSlot> tempTimeSlots = (*it)->getTimeSlots();
             for(int i = 0; i < 48; i++)
             {
                if(((*it)->getTimeSlots()).at(i).isSelected())
                {tempTimeSlots[index_of_list+i].addAttendee(person_name);
                break;
                }
              }
    // ((*it)->getTimeSlots())[index_of_list].addAttendee(person_name); we cannot do this way, i don't know why
             (*it)->setTimeSlots(tempTimeSlots);
         break;}
           count++;
        }
        session->saveEventsToFile();
        for(int i = 0; i < ui->listWidget->count(); i++)
        {ui->listWidget->item(i)->setHidden(false);}
        ui->lineEdit_2->setText("");
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;}
    }
}

void AddingMode::on_pushButton_4_clicked()
{
    ui->lineEdit_2->setText("");
    for(int i = 0; i < ui->listWidget->count(); i++)
    {ui->listWidget->item(i)->setHidden(false);}
}
