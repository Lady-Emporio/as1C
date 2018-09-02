#include "mainwindow.h"

void PhoneTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex currentI=indexAt(event->pos());
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QString codePhone=this->model()->index(row,0).data().toString();
        Settings::S()->MW->sig_openPhone(codePhone,parentOrder);
    }
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

    Phone *new_phone=new Phone(subWindow,"",parentOrder);

    subWindow->setWidget(new_phone);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::sig_openPhone(QString code,QString parentOrder)
{
    {
        QString title="Phone:"+code;
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

        Phone *exist_phone=new Phone(subWindow,code,parentOrder);

        subWindow->setWidget(exist_phone);
        Settings::S()->MW->mdiArea->addSubWindow(subWindow);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();
    }
}


