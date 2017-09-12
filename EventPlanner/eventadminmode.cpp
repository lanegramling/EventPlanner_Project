#include "eventadminmode.h"
#include "ui_eventadminmode.h"
#include <eventplanner.h>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <ctime>

EventAdminMode::EventAdminMode(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventAdminMode),
    session(session)
{
    ui->setupUi(this);

    //initialzation for all value
    setWindowTitle("EventAdmin Mode");
    times = new int[48];
    for(int i = 0; i < 48; i++)
    {times[i] = 0;}
    days = 1;
    months = 1;
    EventName = "N";
    person_name = "/A";
    time_t now = time(0);
    struct tm *date = localtime(&now);
    ui->calendarWidget->setMinimumDate(QDate((date->tm_year)+1900, (date->tm_mon)+1, (date->tm_mday)));
}

EventAdminMode::~EventAdminMode()
{
    session->saveEventsToFile();
    delete ui;
    delete[] times;
}

QString EventAdminMode::Info_Collect(QString &EventName,QString &person_name, int month, int day, int year, int *times)
{
    QString Now ="Do you want to create this event?\n";
    Now = Now + "Event Name:  ";
    Now = Now + person_name;
    Now = Now +"'s ";
    Now = Now + EventName;
    Now = Now + "\nDate: " + QString::number(month) + "\\" + QString::number(day) + "\\" + QString::number(year);
    Now = Now + "\ntimes: ";
    for(int i = 0; i < 48; i++)
    {
        if(times[i] == 1)
        {
            Now = Now + QString::number(i/2);
            Now = Now + ":";
            if(i%2 == 0){
                Now = Now +"00 ";
        }else{
            Now = Now + "30 ";
        }}
    }
    Now = Now + "\n\n[!]Each times is a Start Point ,and each point has 30 min";
    return(Now);
}

void EventAdminMode::receiveshow()
{
    this->show();
}

void EventAdminMode::on_pushButton_2_clicked()
{
    on_pushButton_5_clicked();
    session->saveEventsToFile();
    this->hide();
    emit showEventPlanner();
}



void EventAdminMode::on_pushButton_3_clicked() // use to change times mode to 12-Hour
{
    ui->checkBox->setText("00:00 AM");
    ui->checkBox_2->setText("00:30 AM");
    ui->checkBox_3->setText("01:00 AM");
    ui->checkBox_4->setText("01:30 AM");
    ui->checkBox_5->setText("02:00 AM");
    ui->checkBox_6->setText("02:30 AM");
    ui->checkBox_7->setText("03:00 AM");
    ui->checkBox_8->setText("03:30 AM");
    ui->checkBox_9->setText("04:00 AM");
    ui->checkBox_10->setText("04:30 AM");
    ui->checkBox_11->setText("05:00 AM");
    ui->checkBox_12->setText("05:30 AM");
    ui->checkBox_13->setText("06:00 AM");
    ui->checkBox_14->setText("06:30 AM");
    ui->checkBox_15->setText("07:00 AM");
    ui->checkBox_16->setText("07:30 AM");
    ui->checkBox_17->setText("08:00 AM");
    ui->checkBox_18->setText("08:30 AM");
    ui->checkBox_19->setText("09:00 AM");
    ui->checkBox_20->setText("09:30 AM");
    ui->checkBox_21->setText("10:00 AM");
    ui->checkBox_22->setText("10:30 AM");
    ui->checkBox_23->setText("11:00 AM");
    ui->checkBox_24->setText("11:30 AM");
    ui->checkBox_25->setText("12:00 PM");
    ui->checkBox_26->setText("00:30 PM");
    ui->checkBox_27->setText("01:00 PM");
    ui->checkBox_28->setText("01:30 PM");
    ui->checkBox_29->setText("02:00 PM");
    ui->checkBox_30->setText("02:30 PM");
    ui->checkBox_31->setText("03:00 PM");
    ui->checkBox_32->setText("03:30 PM");
    ui->checkBox_33->setText("04:00 PM");
    ui->checkBox_34->setText("04:30 PM");
    ui->checkBox_35->setText("05:00 PM");
    ui->checkBox_36->setText("05:30 PM");
    ui->checkBox_37->setText("06:00 PM");
    ui->checkBox_38->setText("06:30 PM");
    ui->checkBox_39->setText("07:00 PM");
    ui->checkBox_40->setText("07:30 PM");
    ui->checkBox_41->setText("08:00 PM");
    ui->checkBox_42->setText("08:30 PM");
    ui->checkBox_43->setText("09:00 PM");
    ui->checkBox_44->setText("09:30 PM");
    ui->checkBox_45->setText("10:00 PM");
    ui->checkBox_46->setText("10:30 PM");
    ui->checkBox_47->setText("11:00 PM");
    ui->checkBox_48->setText("11:30 AM");
}

void EventAdminMode::on_pushButton_4_clicked() // use to change times mode to 24-Hour
{
    ui->checkBox->setText("00:00");
    ui->checkBox_2->setText("00:30");
    ui->checkBox_3->setText("01:00");
    ui->checkBox_4->setText("01:30");
    ui->checkBox_5->setText("02:00");
    ui->checkBox_6->setText("02:30");
    ui->checkBox_7->setText("03:00");
    ui->checkBox_8->setText("03:30");
    ui->checkBox_9->setText("04:00");
    ui->checkBox_10->setText("04:30");
    ui->checkBox_11->setText("05:00");
    ui->checkBox_12->setText("05:30");
    ui->checkBox_13->setText("06:00");
    ui->checkBox_14->setText("06:30");
    ui->checkBox_15->setText("07:00");
    ui->checkBox_16->setText("07:30");
    ui->checkBox_17->setText("08:00");
    ui->checkBox_18->setText("08:30");
    ui->checkBox_19->setText("09:00");
    ui->checkBox_20->setText("09:30");
    ui->checkBox_21->setText("10:00");
    ui->checkBox_22->setText("10:30");
    ui->checkBox_23->setText("11:00");
    ui->checkBox_24->setText("11:30");
    ui->checkBox_25->setText("12:00");
    ui->checkBox_26->setText("12:30");
    ui->checkBox_27->setText("13:00");
    ui->checkBox_28->setText("13:30");
    ui->checkBox_29->setText("14:00");
    ui->checkBox_30->setText("14:30");
    ui->checkBox_31->setText("15:00");
    ui->checkBox_32->setText("15:30");
    ui->checkBox_33->setText("16:00");
    ui->checkBox_34->setText("16:30");
    ui->checkBox_35->setText("17:00");
    ui->checkBox_36->setText("17:30");
    ui->checkBox_37->setText("18:00");
    ui->checkBox_38->setText("18:30");
    ui->checkBox_39->setText("19:00");
    ui->checkBox_40->setText("19:30");
    ui->checkBox_41->setText("20:00");
    ui->checkBox_42->setText("20:30");
    ui->checkBox_43->setText("21:00");
    ui->checkBox_44->setText("21:30");
    ui->checkBox_45->setText("22:00");
    ui->checkBox_46->setText("22:30");
    ui->checkBox_47->setText("23:00");
    ui->checkBox_48->setText("23:30");
}

void EventAdminMode::on_lineEdit_textEdited(const QString &arg1)
{   //get edited string(name) from user
    EventName = arg1;
}

void EventAdminMode::on_checkBox_clicked(bool checked)
{times[0] = checked;}
void EventAdminMode::on_checkBox_2_clicked(bool checked)
{times[1] = checked;}
void EventAdminMode::on_checkBox_3_clicked(bool checked)
{times[2] = checked;}
void EventAdminMode::on_checkBox_4_clicked(bool checked)
{times[3] = checked;
}void EventAdminMode::on_checkBox_5_clicked(bool checked)
{times[4] = checked;
}void EventAdminMode::on_checkBox_6_clicked(bool checked)
{times[5] = checked;
}void EventAdminMode::on_checkBox_7_clicked(bool checked)
{times[6] = checked;
}void EventAdminMode::on_checkBox_8_clicked(bool checked)
{times[7] = checked;
}void EventAdminMode::on_checkBox_9_clicked(bool checked)
{times[8] = checked;
}void EventAdminMode::on_checkBox_10_clicked(bool checked)
{times[9] = checked;
}void EventAdminMode::on_checkBox_11_clicked(bool checked)
{times[10] = checked;
}void EventAdminMode::on_checkBox_12_clicked(bool checked)
{times[11] = checked;
}void EventAdminMode::on_checkBox_13_clicked(bool checked)
{times[12] = checked;
}void EventAdminMode::on_checkBox_14_clicked(bool checked)
{times[13] = checked;
}void EventAdminMode::on_checkBox_15_clicked(bool checked)
{times[14] = checked;
}void EventAdminMode::on_checkBox_16_clicked(bool checked)
{times[15] = checked;
}void EventAdminMode::on_checkBox_17_clicked(bool checked)
{times[16] = checked;
}void EventAdminMode::on_checkBox_18_clicked(bool checked)
{times[17] = checked;
}void EventAdminMode::on_checkBox_19_clicked(bool checked)
{times[18] = checked;
}void EventAdminMode::on_checkBox_20_clicked(bool checked)
{times[19] = checked;
}void EventAdminMode::on_checkBox_21_clicked(bool checked)
{times[20] = checked;
}void EventAdminMode::on_checkBox_22_clicked(bool checked)
{times[21] = checked;
}void EventAdminMode::on_checkBox_23_clicked(bool checked)
{times[22] = checked;
}void EventAdminMode::on_checkBox_24_clicked(bool checked)
{times[23] = checked;
}void EventAdminMode::on_checkBox_25_clicked(bool checked)
{times[24] = checked;
}void EventAdminMode::on_checkBox_26_clicked(bool checked)
{times[25] = checked;
}void EventAdminMode::on_checkBox_27_clicked(bool checked)
{times[26] = checked;
}void EventAdminMode::on_checkBox_28_clicked(bool checked)
{times[27] = checked;
}void EventAdminMode::on_checkBox_29_clicked(bool checked)
{times[28] = checked;
}void EventAdminMode::on_checkBox_30_clicked(bool checked)
{times[29] = checked;
}void EventAdminMode::on_checkBox_31_clicked(bool checked)
{times[30] = checked;
}void EventAdminMode::on_checkBox_32_clicked(bool checked)
{times[31] = checked;
}void EventAdminMode::on_checkBox_33_clicked(bool checked)
{times[32] = checked;}
void EventAdminMode::on_checkBox_34_clicked(bool checked)
{times[33] = checked;}
void EventAdminMode::on_checkBox_35_clicked(bool checked)
{times[34] = checked;}
void EventAdminMode::on_checkBox_36_clicked(bool checked)
{times[35] = checked;}
void EventAdminMode::on_checkBox_37_clicked(bool checked)
{times[36] = checked;}
void EventAdminMode::on_checkBox_38_clicked(bool checked)
{times[37] = checked;}
void EventAdminMode::on_checkBox_39_clicked(bool checked)
{times[38] = checked;}
void EventAdminMode::on_checkBox_40_clicked(bool checked)
{times[39] = checked;}
void EventAdminMode::on_checkBox_41_clicked(bool checked)
{times[40] = checked;}
void EventAdminMode::on_checkBox_42_clicked(bool checked)
{times[41] = checked;}
void EventAdminMode::on_checkBox_43_clicked(bool checked)
{times[42] = checked;}
void EventAdminMode::on_checkBox_44_clicked(bool checked)
{times[43] = checked;}
void EventAdminMode::on_checkBox_45_clicked(bool checked)
{times[44] = checked;}
void EventAdminMode::on_checkBox_46_clicked(bool checked)
{times[45] = checked;}
void EventAdminMode::on_checkBox_47_clicked(bool checked)
{times[46] = checked;}
void EventAdminMode::on_checkBox_48_clicked(bool checked)
{times[47] = checked;}

void EventAdminMode::on_pushButton_clicked()
{
    int count = 0;
    for(int i = 0; i < 48; i++)
    { if(times[i] == 1)
        {count++;}
    }
    if((count == 0)||(EventName == "N")||(person_name == "/A"))
    {QMessageBox::warning(this,"Warning!!","Please Check Name and Your times!!!");}
    else{
    switch(QMessageBox::question(this,"Sure??",Info_Collect(EventName,person_name,ui->calendarWidget->selectedDate().month(),
                                                            ui->calendarWidget->selectedDate().day(), ui->calendarWidget->selectedDate().year(), times),
                         QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        session->addEvent(person_name,EventName,ui->calendarWidget->selectedDate().month(),
                          ui->calendarWidget->selectedDate().day(), ui->calendarWidget->selectedDate().year(), times);
        on_pushButton_5_clicked();
        session->saveEventsToFile();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }}
    return;
}

void EventAdminMode::on_lineEdit_2_textChanged(const QString &arg1)
{
 person_name = arg1;
}

void EventAdminMode::on_pushButton_5_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    EventName = "N";
    person_name = "/A";
    for(int i = 0; i < 48; i++)
    {times[i] = 0;}
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_10->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_14->setChecked(false);
    ui->checkBox_15->setChecked(false);
    ui->checkBox_16->setChecked(false);
    ui->checkBox_17->setChecked(false);
    ui->checkBox_18->setChecked(false);
    ui->checkBox_19->setChecked(false);
    ui->checkBox_20->setChecked(false);
    ui->checkBox_21->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->checkBox_23->setChecked(false);
    ui->checkBox_24->setChecked(false);
    ui->checkBox_25->setChecked(false);
    ui->checkBox_26->setChecked(false);
    ui->checkBox_27->setChecked(false);
    ui->checkBox_28->setChecked(false);
    ui->checkBox_29->setChecked(false);
    ui->checkBox_30->setChecked(false);
    ui->checkBox_31->setChecked(false);
    ui->checkBox_32->setChecked(false);
    ui->checkBox_33->setChecked(false);
    ui->checkBox_34->setChecked(false);
    ui->checkBox_35->setChecked(false);
    ui->checkBox_36->setChecked(false);
    ui->checkBox_37->setChecked(false);
    ui->checkBox_38->setChecked(false);
    ui->checkBox_39->setChecked(false);
    ui->checkBox_40->setChecked(false);
    ui->checkBox_41->setChecked(false);
    ui->checkBox_42->setChecked(false);
    ui->checkBox_43->setChecked(false);
    ui->checkBox_44->setChecked(false);
    ui->checkBox_45->setChecked(false);
    ui->checkBox_46->setChecked(false);
    ui->checkBox_47->setChecked(false);
    ui->checkBox_48->setChecked(false);
}
