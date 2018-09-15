#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent = 0);
signals:

public slots:
    void wheelEvent(QWheelEvent * event ){}
};

#endif // MYCOMBOBOX_H
