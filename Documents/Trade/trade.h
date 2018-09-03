#ifndef TRADE_H
#define TRADE_H

#include "Settings/settings.h"
#include "BaseObject/basechoose.h"

class ChooseDealer:public QLineEdit
{
public:
    ChooseDealer(QWidget *parent):QLineEdit(parent){}
    void keyPressEvent(QKeyEvent *event);
};

class Trade : public QWidget
{
    Q_OBJECT
    QString code;
    void makeGui();
    QLabel*_idRec;
    QLabel*_dateRec;
    QComboBox*_statusRec;
    QLineEdit*_ordersRec;
    ChooseDealer*_dealerRec;
    QTextEdit*_commentRec;
    QLineEdit*color_optionRec;
    LabelChoose*giveAwayCarRec;
    QLineEdit*giveAwayVinRec;
    QDateEdit*giveAwayDateRec;
    LabelChoose*getCarRec;
    QLineEdit*getVinRec;
    QDateEdit*getDateRec;
public:
    explicit Trade(QWidget *parent,QString code);

signals:

public slots:
};

#endif // TRADE_H
