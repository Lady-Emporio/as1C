#ifndef TRADE_LIST_H
#define TRADE_LIST_H

#include "BaseObject/basetable.h"


class Trade_list : public BaseTable
{
    Q_OBJECT
public:
    explicit Trade_list(QWidget *parent = 0);

signals:

public slots:
    void action_addRow();
    void sig_open_trade();
};

#endif // TRADE_LIST_H
