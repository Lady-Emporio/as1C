#include "mainwindow.h"

void Trade_list::action_addRow()
{
    QString title="New trade";
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

    Trade *new_trade=new Trade(subWindow,"");

    subWindow->setWidget(new_trade);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
