#ifndef EVENTADMINMODE_H
#define EVENTADMINMODE_H
#include <QDialog>
namespace Ui {
class EventAdminMode;
}
class EventAdminMode : public QDialog
{
    Q_OBJECT

public:
    explicit EventAdminMode(QWidget *parent = 0);
    ~EventAdminMode();
private:
    Ui::EventAdminMode *ui;

private slots:

signals:
};

#endif // EVENTADMINMODE_H
