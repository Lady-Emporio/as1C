#include "mainwindow.h"
void Orders_list::action_addRow()
{
    QString title="New order";
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

    Order *new_order=new Order(subWindow,"");

    subWindow->setWidget(new_order);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();

}

void Orders_list::action_Armors()
{
    if(tableTree->currentIndex()!=QModelIndex()){
        QString code=tableTree->model()->index(tableTree->currentIndex().row(),0).data().toString();
        Settings::S()->MW->sig_openArmor(code);
    }
}



void OrdersTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    if("Order list"==table_name){
        QModelIndex currentI=indexAt(event->pos());
        if(currentI!=QModelIndex()){
            int row=currentI.row();
            QString codeOrders=this->model()->index(row,0).data().toString();
            Settings::S()->MW->sig_openOrder(codeOrders);
        }
    }
}

void MainWindow::sig_openOrder(QString code)
{
    QString title="Order:"+code;
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

    Order *exist_order=new Order(subWindow,code);

    subWindow->setWidget(exist_order);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::sig_openArmor(QString orderCode)
{
    QString title="Armor for:"+orderCode;
    QList<QMdiSubWindow *>	allSub=mdiArea->subWindowList();
    for(auto x:allSub){
        if(x->windowTitle()==title){
            mdiArea->setActiveSubWindow(x);
            x->move(0,0);
            return;
        };
    };
    QMdiSubWindow *subWindow = new QMdiSubWindow(mdiArea);
    subWindow->setWindowTitle(title);

    QString armorText=neutral_getArmor(orderCode);

    QLineEdit *armorView=new QLineEdit(armorText,subWindow);
    subWindow->setWidget(armorView);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
    subWindow->setFixedWidth(700);
    mdiArea->setActiveSubWindow(subWindow);
    subWindow->move(0,0);
}


void MainWindow::sig_chooseCar(QWidget *senderOrder)
{
    QString title="Choose car"+senderOrder->objectName();
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

    baseChoose *new_order=new baseChoose(subWindow,"cars","_folder=1",senderOrder);

    subWindow->setWidget(new_order);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}


void LabelChoose::mouseDoubleClickEvent(QMouseEvent *)
{
    Settings::S()->MW->sig_chooseCar(realParent);
}

void TableChoose::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex currentI=this->indexAt(event->pos());
    if(currentI!=QModelIndex()){
        int row=currentI.row();
        QSqlRelationalTableModel *model=(QSqlRelationalTableModel*)this->model();
        QString toParent=model->index(row,0).data().toString();
        QString filter="_parentCode='"+toParent+"'";
        if(model->filter()!=filter){
            if(model->index(row,4).data().toInt()==1){
                model->setFilter(filter);
                baseChoose*parentChoose=(baseChoose*)this->parentWidget();
                parentChoose->forFilter->setText(filter);
                parentChoose->historyFilters.append(filter);
            }else{
                if("New order"==realParent->objectName() || realParent->objectName().startsWith("Order:")){
                    QString chooseIndex=model->index(row,0).data().toString();
                    QString chooseName=model->index(row,2).data().toString();
                    Order *par=(Order *)realParent;
                    par->setChooseCar(chooseIndex,chooseName);
                    QList<QMdiSubWindow *>	allSub=Settings::S()->MW->mdiArea->subWindowList();
                    for(auto x:allSub){
                        if(x->widget()==this->parent()){
                            x->close();
                            return;
                        };
                    };
                }
            }
        }
    }
}


void Order::action_phones_list()
{
    QString title="Phones list for:"+code;
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

    PhonesList *phonesList=new PhonesList(subWindow,code);

    subWindow->setWidget(phonesList);
    Settings::S()->MW->mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void Order::action_getArmor()
{
    Settings::S()->MW->sig_openArmor(this->code);
}
