#ifndef SUBTABLE_H
#define SUBTABLE_H

#include "BaseObject/basetable.h"

class Subtable : public BaseTable
{
    Q_OBJECT
public:
    int indexColumnToHide;
    int parentColumnToHide;
    QString parentIndex;
    int dateIndex;
    explicit Subtable(QWidget *parent, int indexColumnToHide, int parentColumnToHide, QString parentIndex, int dateIndex=-1);

signals:

public slots:
    void action_addRow();
    void hideColumn();
};

#endif // SUBTABLE_H
