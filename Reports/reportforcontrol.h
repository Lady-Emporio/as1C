#ifndef REPORTFORCONTROL_H
#define REPORTFORCONTROL_H

#include "Settings/settings.h"

class ReportForControl : public QWidget
{
    Q_OBJECT
    void makeGui();
    QDateTimeEdit *beginPar;
    QDateTimeEdit *endPar;
    QTextDocument   * m_document;
    QTextCursor    * m_cursor;
    QTextEdit * docView;
    QTextTable *table;
    void setTitle();
    void setTable();
    void getSqlTable();
public:

    explicit ReportForControl(QWidget *parent = 0);

signals:

public slots:
    void action_CreateReport();
};

#endif // REPORTFORCONTROL_H
