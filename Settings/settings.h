#ifndef SETTINGS_H
#define SETTINGS_H

#include "allinclude.h"
class MainWindow;
class Settings
{
    QMap<QString,QString>parameters;
    Settings();
    bool openDB();
    void createTables();
    void readParamsFromJson();
    void writeParamsToJson();
    void insertParamsInJson(QString key, QString value);
    void SetDefaultParams();
public:
    MainWindow * MW;
    QSqlDatabase _db;
    static QStringList keys();
    static Settings *S();
    static QString get(QString par);
    static void set(QMap<QString,QString>par);
    static void GetErrorMessage(QSqlQuery *query=nullptr,QString transaction="");
    static QString shieldInection(QString text);
};

#endif // SETTINGS_H
