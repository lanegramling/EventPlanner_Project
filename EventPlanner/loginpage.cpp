#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

LoginPage::LoginPage(Session *session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage),
    session(session)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage() {

}

void LoginPage::on_loginButton_clicked() {
    if (userName == "") {
        QMessageBox::warning(this,"Invalid User Name!","User name was left empty.");
    } else if (userName.contains("\"")) {
        QMessageBox::warning(this,"Invalid User Name!","User name may not contain quotation marks.");
    } else if (userName.length() > 50) {
        QMessageBox::warning(this,"Invalid User Name!","User name must be less than 50 characters.");
    } else {
        session->setUser(userName);
        this->hide();
        emit goToEventPlanner();
    }

}

void LoginPage::on_userNameText_textEdited(const QString &arg1) {
    userName = arg1;
}

void LoginPage::receiveShow() {
    userName = "";
    ui->userNameText->clear();
    this->show();
}
