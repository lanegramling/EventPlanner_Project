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
    Ui::LoginPage *ui;
    Session *session;
    QString userName;

private slots:
    void on_loginButton_clicked();
    void on_userNameText_textEdited(const QString &arg1);
    void receiveShow();


signals:
    /*!
     * \brief goToEventPlanner
     * \details Signal for transitiong to the Event Planner page.
     */
    void goToEventPlanner();
};

#endif // LOGINPAGE_H
