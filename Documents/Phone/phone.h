#ifndef PHONE_H
#define PHONE_H

#include <QWidget>

class Phone : public QWidget
{
    Q_OBJECT
public:
    explicit Phone(QWidget *parent ,QString code);

signals:

public slots:
};

#endif // PHONE_H
