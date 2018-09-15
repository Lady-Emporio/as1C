#ifndef DESTINYTRADE_H
#define DESTINYTRADE_H

#include "Settings/settings.h"

class DestinyTrade : public QWidget
{
    Q_OBJECT
    QString code;
    void makeGui();
public:
    QLabel *vinCar; //trade._getCar as _getCar
    QLabel *orderPresentation;//orders._presentation
    QLabel *parentTrade;
    QLineEdit *boughtClient;
    MyComboBox *soldManager;
    QDateEdit*dateSold;
    QLineEdit*comment;
    explicit DestinyTrade(QWidget *parent,QString code);

signals:

public slots:
    void UPDATE_destiny();
    void SELECT_destiny();
};

#endif // DESTINYTRADE_H
