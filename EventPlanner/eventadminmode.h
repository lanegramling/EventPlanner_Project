#ifndef EVENTADMINMODE_H
#define EVENTADMINMODE_H
#include <QMainWindow>
#include <QDebug>
#include "session.h"
#include "helpermethods.h"
namespace Ui {
class EventAdminMode;
}
/*!
 * \brief The EventAdminMode class
 * \details Window used for creating new events.
 */
class EventAdminMode : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief EventAdminMode
     * \details Constructor for EventAdminMode
     * \param session
     * \param parent
     */
    explicit EventAdminMode(Session *session, QWidget *parent = 0);
    ~EventAdminMode();

    /*!
     * \brief Info_Collect
     * \details Formats a QString for displaying Event contents.
     * \param EventName
     * \param person_name
     * \param month
     * \param day
     * \param year
     * \return QString
     */
    QString Info_Collect(QString &EventName,QString person_name, int month, int day, int year);
    // use to make all Information to a string, used for "Make Sure"

    /*!
     * \brief setStyle_calendarWidget
     * \details Set a style sheet for calender widget.
     */
    void setStyle_calendarWidget();
private:
    /*!
     * \brief ui
     */
    Ui::EventAdminMode *ui;
    /*!
     * \brief months
     */
    int months; // month
    /*!
     * \brief days
     */
    int days;   // day
    /*!
     * \brief EventName
     */
    QString EventName; // Event Name

    /*!
     * \brief session
     * \details Session passed between all classes to hold events.
     */
    Session *session;
    /*!
     * \brief set12HourFormat
     * \details Tracks which time format is being displayed.
     */
    bool set12HourFormat = true;
    /*!
     * \brief timeSlots
     */
    QList<int> timeslots;
    /*!
     * \brief resetTimeSlotsWidget
     * \details Clears and then refills the time slot list with time slots that have TimeSlot.isSelected().
     */
    void resetTimeSlotsWidget();

    /*!
     * \brief on_pushButton_5_clicked
     * \details Resets the EventAdminMode window.
     */
    void on_pushButton_5_clicked();// member function

private slots:
    /*!
     * \brief receiveshow
     * \details Called when recieives signal to show window.
    */
    void receiveshow();


    /*!
     * \brief on_saveButton_clicked
     * \details Verifies page contents and provides feedback. If contents are complete, calls Session.addEvent() with provided information. Then calls Session.saveEventsToFile() and on_pushButton_5_clicked().
     */
    void on_saveButton_clicked();

    /*!
     * \brief on_backButton_clicked
     * \details Calls on_pushButton_5_clicked(). Hides windows and then emits showEventPlanner().
     */
    void on_backButton_clicked();

    /*!
     * \brief on_set12Hour_clicked
     * \details Resets the time slot selection boxes with 12 hour clock formatted times then resetTimeSlotsWidget().
     */
    void on_set12Hour_clicked();

    /*!
     * \brief on_set24Hour_clicked
     * \details Resets the time slot selection boxes with 24 hour clock formatted times then resetTimeSlotsWidget().
     */
    void on_set24Hour_clicked();

    /*!
     * \brief on_addTimeSlots_clicked
     * \details Calls TimeSlot.setTrue() for the range on time slots in the dropped down boxes. The calls resetTimeSlotsWidget().
     */
    void on_addTimeSlots_clicked();

    /*!
     * \brief on_clearTimeSlotsButton_clicked
     * \details Calls TimeSlot.clearTimeSlot() on all of the time slots in the timeSlots variable. Then calls resetTimeSlotsWidget().
     */
    void on_clearTimeSlotsButton_clicked();

    /*!
     * \brief on_eventNameTextBox_textEdited
     * \details Updates EventName variable whenever the eventNameTextBox is editted.
     * \param arg1
     */
    void on_eventNameTextBox_textEdited(const QString &arg1);

signals:
    /*!
     * \brief showEventPlanner
     * \details Signal to go back to the EventPlanner.
     */
    void showEventPlanner();

    /*!
     * \brief quit
     * \details Signal to quit EventAdminMode.
     */
    void quit();
};

#endif // EVENTADMINMODE_H
