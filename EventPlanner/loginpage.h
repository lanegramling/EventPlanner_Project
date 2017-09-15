#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "session.h"

#include <QMainWindow>

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
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
    void goToEventPlanner();
};

#endif // LOGINPAGE_H
