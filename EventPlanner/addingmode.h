#ifndef ADDINGMODE_H
#define ADDINGMODE_H
#include <QMainWindow>
#include "session.h"
#include "event.h"
#include "helpermethods.h"
#include "attendee.h"
#include <list>
namespace Ui{
class AddingMode;
}

/*!
 * \brief The AddingMode class
 * \details Class for adding availablity to an event.
 */
class AddingMode : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief AddingMode
     * \details Constructor for the Adding Mode
     * \param session
     * \param parent
     */
    explicit AddingMode(Session *session, QWidget *parent = 0);

    ~AddingMode();
private:

    /*!
     * \brief ui
     */
    Ui::AddingMode *ui;

    /*!
     * \brief EventIndex
     * \details Holds index of the selected Event.
     */
    int EventIndex;

    /*!
     * \brief EventName
     */
    QString EventName;

    /*!
     * \brief month
     */
    int month;

    /*!
     * \brief year
     */
    int year;

    /*!
     * \brief day
     */
    int day;

    bool format = false;

    /*!
     * \brief session
     * \details Session passed between all classes to hold events.
     */
    Session *session;
private slots:

    /*!
     * \brief receiveshow
     * \details Function called when class receives signal to become visibale. Sets visiblity to true.
     */
    void receiveshow();

    /*!
     * \brief on_btnBack_clicked
     * \details Function called when Back button is clicked. Emits showEventPlanner()
     */
    void on_btnBack_clicked();

    /*!
     * \brief on_wListEvents_clicked
     * \details Called when an Event in the Event list is clicked on. Fills TimeSlot list with time slots for the event where TimeSlot.isSelected() true.
     * \param index
     */
    void on_wListEvents_clicked(const QModelIndex &index);

    /*!
     * \brief on_wListTimeslots_clicked
     * \details Called when a TimeSlot is clicked on in the Time Slot list. Fills the Attendees list for the selected time slot.
     * \param index
     */
    void on_wListTimeslots_clicked(const QModelIndex &index);

    /*!
     * \brief on_addToTimeSlotButton_clicked
     * \details Called when Add Me to Time Slot button is clicked. Adds the current user (Session.getUser()) to the selected time slot.
     */
    void on_addToTimeSlotButton_clicked();
signals:

    /*!
     * \brief showEventPlanner
     * \details Signal for switch back to the Event Planner
     */
    void showEventPlanner();
};
#endif // ADDINGMODE_H
