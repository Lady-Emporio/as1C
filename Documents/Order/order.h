#ifndef ORDER_H
#define ORDER_H

#include "allinclude.h"
#include "BaseObject/basechoose.h"
#include "BaseObject/basetable.h"
#include "BaseObject/subtable.h"
class Order : public QWidget
{
    Q_OBJECT
    void makeGui();
    LabelChoose *carChooseLabel;
    QLineEdit * idRec;
    QLabel * dateRec;
    MyComboBox * managerRec;
    QLineEdit * clientRec;
    QLineEdit *rlRec;
    MyComboBox *statusRec;
    MyComboBox *order_stock;
    QString code;
    QString dateCreate;
    QString indexCar;
    Subtable*subCommentTable;
    Subtable*subOptionTable;
    Subtable*subColorTable;
    void itsNew();
    bool DELETEIfNotCreate;
    ~Order();
public:
    void setChooseCar(QString indexCar,QString nameCar);
    explicit Order(QWidget *parent,QString code);

signals:

public slots:
    void UPDATE_orders();
    void SELECT_order();
    void action_phones_list();
    void action_getArmor();
};

#endif // ORDER_H
