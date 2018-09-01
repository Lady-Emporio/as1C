#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "allinclude.h"
#include "Settings/settings.h"
#include "Settings/settings_gui.h"
#include "BaseObject/basetable.h"
#include "Documents/Orderslist/orders_list.h"
#include "Documents/Order/order.h"
#include "Documents/Phone/phoneslist.h"
#include "Documents/Phone/phone.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    void makeGui();
private slots:
    void action_Settings();
    void action_active_OrdersList();
    void action_OrdersList();
    void action_Phones();
public:
    QMdiArea * mdiArea;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
//order:
    void sig_chooseCar(QWidget *senderOrder);
    void sig_openOrder(QString code);
//phones

};

#endif // MAINWINDOW_H
