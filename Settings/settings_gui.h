#ifndef SETTINGS_GUI_H
#define SETTINGS_GUI_H

#include "Settings/settings.h"
#include "allinclude.h"
class Settings_gui : public QWidget
{
    Q_OBJECT
    QMap<QString,QLineEdit*>edits;
    void makeGui();
public:
    explicit Settings_gui(QWidget *parent = 0);
public slots:
    void setValue();
    void choosedb();
    void chooseImageApp();
    void writeInSettingsValue();
};

#endif // SETTINGS_GUI_H
