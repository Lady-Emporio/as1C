#include "mainwindow.h"

void DealerTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex currentI=this->indexAt(event->pos());
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QSqlTableModel *model=(QSqlTableModel*)this->model();
        QString dealerCode=model->index(row,0).data().toString();
        Settings::S()->MW->sig_openDealer(dealerCode);
    }
}


void MainWindow::sig_openDealer(QString code, QMap<QString, QString> *par)
{
    QString title="Dealer:"+code;
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

    Dealers *exist_dealer=new Dealers(subWindow,code,par);

    subWindow->setWidget(exist_dealer);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
