#ifndef TRADE_H
#define TRADE_H

#include "Settings/settings.h"
#include "BaseObject/basechoose.h"

class Trade : public QWidget
{
    Q_OBJECT
    QString code;
    void makeGui();
    void itsNew();
    QLabel*_idRec;
    QLabel*_dateRec;
    QString dateCreate;
    QComboBox*_statusRec;
    QLineEdit*_ordersRec;
    QLabel*_ordersPresentation;
    QLineEdit*_dealerRec;
    QLabel* dealerName;
    QTextEdit*_commentRec;
    QLineEdit*color_optionRec;
    LabelChoose*giveAwayCarRec;
    QLineEdit*giveAwayVinRec;
    QDateEdit*giveAwayDateRec;
    LabelChoose*getCarRec;
    QLineEdit*getVinRec;
    QDateEdit*getDateRec;
    QString GiveAwayCarIndexChoose;
    QString GiveAwayCarNameChoose;
    QString getCarIndexChoose;
    QString getCarNameChoose;
    ~Trade();
    bool DELETEIfNotCreate;
public:
    explicit Trade(QWidget *parent,QString code);
    void setChooseCar(QString chooseIndex,QString chooseName,QString labelName);
signals:

public slots:
    void sig_selectDealers();
    void sig_selectOrders();
    void UPDATE_trade();
    void SELECT_trade();
};

#endif // TRADE_H
