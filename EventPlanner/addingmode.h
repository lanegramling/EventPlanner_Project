#ifndef ADDINGMODE_H
#define ADDINGMODE_H
#include <QMainWindow>
#include "session.h"
#include "event.h"
#include <list>
namespace Ui{
class AddingMode;
}
class AddingMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddingMode(Session *session, QWidget *parent = 0);
    ~AddingMode();
private:
    Ui::AddingMode *ui;

    QString person_name;   // adding data

    //searching data

    int EventIndex;
    QString EventName;
    int month;
    int year;
    int day;
    Session *session;
private slots:
    void receiveshow();
    void on_pushButton_2_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_listWidget_2_clicked(const QModelIndex &index);

    void on_addToTimeSlotButton_clicked();
signals:
    void showEventPlanner();
};
#endif // ADDINGMODE_H
