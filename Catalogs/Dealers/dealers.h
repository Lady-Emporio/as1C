#ifndef DEALERS_H
#define DEALERS_H

#include "Settings/settings.h"
#include "BaseObject/subtable.h"
class Dealers : public QWidget
{
    Q_OBJECT
    QString code;

    QLineEdit*codeEdit;
    QLineEdit*nameEdit;
    QTextEdit*commentEdit;
    QLineEdit*activePhoneEdit;
    QLineEdit*distryPhoneEdit;
    Subtable*email;
    Subtable*full_call;
    QPushButton*hideFullCallButton;
    QPushButton*hideEmailButton;
    void makeGui();
    void insertFromPhone(QMap<QString,QString> par);
public:
    explicit Dealers(QWidget *parent,QString code,QMap<QString,QString>*par=nullptr);
signals:
public slots:
    void action_HideFullCall();
    void action_HideEmail();
    void action_WriteInDB();
    void fillAll();
};

#endif // DEALERS_H
