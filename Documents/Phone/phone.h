#ifndef PHONE_H
#define PHONE_H

#include "BaseObject/subtable.h"
#include "BaseObject/delegate.h"
#include "Documents/Call/call.h"



class Phone : public QWidget
{
    Q_OBJECT
    Call * callsTable;
    QLineEdit * idRec;
    QLabel * dateRec;
    QLineEdit * orderRec;
    QComboBox * statucRec;
    QLabel * orders_presentation;
    void makeGui();
    void itsNew();
    bool DELETEIfNotCreate;
    ~Phone();
    QString code;
    QString dateCreate;
    QString parentOrder;

    QString getOrderPresentation(QString orderId);
public:
    explicit Phone(QWidget *parent , QString code, QString parentOrder);

signals:

public slots:
    void UPDATE_phone();
    void SELECT_phone();
};

#endif // PHONE_H
