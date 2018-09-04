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

void Trade_list::sig_open_trade()
{
    QModelIndex currentI=tableView->currentIndex();
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QSqlTableModel *model=(QSqlTableModel*)tableView->model();
        QString tradeCode=model->index(row,0).data().toString();
        Settings::S()->MW->sig_openTrade(tradeCode);
    }
}

void MainWindow::sig_openTrade(QString code)
{
    QString title="Trade:"+code;
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

    Trade *exist_trade=new Trade(subWindow,code);

    subWindow->setWidget(exist_trade);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
