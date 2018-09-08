#include "mainwindow.h"
void DestinyList::sig_open_desniny()
{
    QModelIndex selectIndex=tableView->currentIndex();
    if(QModelIndex()!=selectIndex){
        int row=selectIndex.row();
        QString code=tableView->model()->index(row,0).data().toString();


        QString title="Destiny:"+code;
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

        DestinyTrade *exist_destiny=new DestinyTrade(subWindow,code);

        subWindow->setWidget(exist_destiny);
        Settings::S()->MW->mdiArea->addSubWindow(subWindow);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();


    }
}
