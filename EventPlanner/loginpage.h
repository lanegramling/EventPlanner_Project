#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "session.h"
#include <QMainWindow>

namespace Ui {
class LoginPage;
}

/*!
 * \brief The LoginPage class
 * \details Class for buidling the Login Page
 */
class LoginPage : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief LoginPage
     * \details Constructor for LoginPage class
     * \param session
     * \param parent
     */
    explicit LoginPage(Session * session, QWidget *parent = 0);
    ~LoginPage();

private:
    /*!
     * \brief ui
     */
    Ui::LoginPage *ui;
    /*!
     * \brief session
     * \details Session passed between all classes to hold events.
     */
    Session *session;
    /*!
     * \brief userName
     */
    QString userName;

private slots:
    /*!
     * \brief on_loginButton_clicked
     * \details Checks validity of user name. If valid, calls Session.setUser() and emits goToEventPlanner().
     */
    void on_loginButton_clicked();

    /*!
     * \brief on_userNameText_textEdited
     * \details Updates userName with arg1 whenever userNameText is editted.
     * \param arg1
     */
    void on_userNameText_textEdited(const QString &arg1);

    /*!
     * \brief receiveShow
     * \details Called whenever signal is received to display LoginPage.
     */
    void receiveShow();

    /*!
     * \brief on_quitButton_clicked
     * \details Quits appliction.
     */
    void on_quitButton_clicked();


signals:
    /*!
     * \brief goToEventPlanner
     * \details Signal for transitiong to the Event Planner page.
     */
    void goToEventPlanner();
};

#endif // LOGINPAGE_H
