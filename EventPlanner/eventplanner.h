#ifndef EVENTPLANNER_H
#define EVENTPLANNER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>

namespace Ui {
class EventPlanner;
}

/*!
 * \brief The EventPlanner class
 * \details Main menu window with options to either go to EventAdminMode or AddingMode
 */
class EventPlanner : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief EventPlanner
     * \details Construtor for menu window of main page.
     * \param parent
     */
    explicit EventPlanner(QWidget *parent = 0);
    ~EventPlanner();

    /*!
     * \brief setPicture
     * \details Adds picture to menu screen.
     */
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
    /*!
     * \brief AddingModeshow
     * \details Signal to switch to Adding Mode for adding availablity
     */
    void AddingModeshow(); // show mode adding window

    /*!
     * \brief AddingnModequit
     * \details Signal that Addinf Mode was left
     */
    void AddingnModequit(); // quit signal for mode adding

    /*!
     * \brief AdminModeshow
     * \details Signal to show Admin mode for creating events
     */
    void AdminModeshow(); // show mode Event admin mode

    /*!
     * \brief AdminModequit
     * \details Signal to say that Admin mode was exitted
     */
    void AdminModequit(); // quit signal for mode admin
};

#endif // EVENTPLANNER_H
