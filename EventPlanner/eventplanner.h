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
    /*!
     * \brief ui
     */
    Ui::EventPlanner *ui;

private slots:
    /*!
     * \brief receiveShow
     * \details Called when signal from LoginPage is received to show the EventPlanner
     */
    void receiveShow();

    /*!
     * \brief getMode1
     * \details Called when signal from EventAdminMode is received to show the EventPlanner
     */
    void getMode1();

    /*!
     * \brief getMode2
     * \details Called when signal from AddingMode is received to show the EventPlanner
     */
    void getMode2();

    /*!
     * \brief on_pushButton_clicked
     * \details Hides window and emits AddingModeshow().
     */
    void on_pushButton_clicked();// use for Adding mode

    /*!
     * \brief on_pushButton_2_clicked
     * \details Hides window and emits AdminModeshow().
     */
    void on_pushButton_2_clicked();// use for Event Admin mode

    /*!
     * \brief on_pushButton_4_clicked
     * \details Opens QMessageBox for About Us.
     */
    void on_pushButton_4_clicked();// use for Help

    /*!
     * \brief on_pushButton_3_clicked
     * \details Opens QMessageBox for Help.
     */
    void on_pushButton_3_clicked();// use for AboutUs

    /*!
     * \brief on_logoutButton_clicked
     * \details Hide EventPlanner and emits Logout().
     */
    void on_logoutButton_clicked();

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

    /*!
     * \brief Logout
     * \details Signal to return to Login Page
     */
    void Logout();
};

#endif // EVENTPLANNER_H
