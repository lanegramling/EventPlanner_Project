#ifndef EVENTPLANNER_H
#define EVENTPLANNER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>

namespace Ui {
class EventPlanner;
}

class EventPlanner : public QMainWindow
{
    Q_OBJECT

public:
    explicit EventPlanner(QWidget *parent = 0);
    ~EventPlanner();

    void setPicture();

private:
    Ui::EventPlanner *ui;

private slots:
    void getMode1();
    void getMode2();

    void on_pushButton_clicked();// use for Adding mode

    void on_pushButton_2_clicked();// use for Event Admin mode

    void on_pushButton_4_clicked();// use for Help

    void on_pushButton_3_clicked();// use for AboutUs

signals:
    void AddingModeshow(); // show mode adding window
    void AddingnModequit(); // quit signal for mode adding
    void AdminModeshow(); // show mode Event admin mode
    void AdminModequit(); // quit signal for mode admin
};

#endif // EVENTPLANNER_H
