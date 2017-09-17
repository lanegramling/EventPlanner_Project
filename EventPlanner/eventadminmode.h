#ifndef EVENTADMINMODE_H
#define EVENTADMINMODE_H
#include <QMainWindow>
#include <QDebug>
#include "session.h"
#include "timeslot.h"
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
     *\brief TIME_ARRAY_12H
     * \details Holds times for 12 hour format.
     */
    const QStringList TIME_ARRAY_12H = {"12:00 AM", "12:30 AM", "1:00 AM", "1:30 AM", "2:00 AM", "2:30 AM", "3:00 AM", "3:30 AM",
                                  "4:00 AM", "4:30 AM", "5:00 AM", "5:30 AM", "6:00 AM", "6:30 AM", "7:00 AM", "7:30 AM",
                                  "8:00 AM", "8:30 AM","9:00 AM", "9:30 AM", "10:00 AM", "10:30 AM", "11:00 AM", "11:30 AM",
                                  "12:00 PM", "12:30 PM", "1:00 PM", "1:30 PM", "2:00 PM", "2:30 PM", "3:00 PM", "3:30 PM",
                                  "4:00 PM", "4:30 PM", "5:00 PM", "5:30 PM", "6:00 PM", "6:30 PM", "7:00 PM", "7:30 PM",
                                  "8:00 PM", "8:30 PM","9:00 PM", "9:30 PM", "10:00 PM", "10:30 PM", "11:00 PM", "11:30 PM"};

    /*!
     *\brief TIME_ARRAY_24H
     * \details Holds times for 24 gour format.
     */
    const QStringList TIME_ARRAY_24H = {"00:00", "00:30", "01:00", "01:30", "02:00", "02:30", "03:00", "03:30",
                                       "04:00", "04:30", "05:00", "05:30", "06:00", "06:30", "07:00", "07:30",
                                       "08:00", "08:30", "09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
                                       "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30",
                                       "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30",
                                       "20:00", "20:30", "21:00", "21:30", "22:00", "22:30", "23:00", "23:30"};
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
    QList<TimeSlot> timeSlots;
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
