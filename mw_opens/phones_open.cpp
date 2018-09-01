#include "mainwindow.h"

void PhoneTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"phones table click";
}

void PhonesList::action_addRow()
{
    QString title="New phone";
    QList<QMdiSubWindow *>	allSub=Settings::S()->MW->mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            Settings::S()->MW->mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(Settings::S()->MW->mdiArea);
    subWindow->setWindowTitle(title);

    Phone *new_phone=new Phone(subWindow,"");

    subWindow->setWidget(new_phone);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
