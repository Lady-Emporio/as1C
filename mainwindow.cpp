#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    makeGui();
}
void MainWindow::makeGui()
{

    mdiArea=new QMdiArea(this);
    this->setCentralWidget(mdiArea);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QMenuBar * mainMenu=new QMenuBar(this);
    this->setMenuBar(mainMenu);
    mainMenu->addAction("Active Orders",this,SLOT(action_active_OrdersList()));
    mainMenu->addAction("Settings",this,SLOT(action_Settings()));
    QMenu *docMenu=new QMenu("Documents",mainMenu);
    mainMenu->addMenu(docMenu);
    docMenu->addAction("All orders",this,SLOT(action_OrdersList()));
    docMenu->addAction("Phones",this,SLOT(action_Phones()));
//    QMenu *catalogs=new QMenu("Catalogs",mainMenu);
//    mainMenu->addMenu(catalogs);
//    catalogs->addAction("Cars",this,SLOT(action_CarsList()));

}
void MainWindow::action_Phones(){
    QString title="Phones list";
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

    PhonesList *phonesList=new PhonesList(subWindow,"");

    subWindow->setWidget(phonesList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_Settings()
{
    QString title="Settings";
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
    Settings_gui *setting=new Settings_gui(subWindow);
    subWindow->setWidget(setting);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_active_OrdersList()
{
    QString title="Active orders";
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

    Orders_list *active_OrdersList=new Orders_list(subWindow,true);

    subWindow->setWidget(active_OrdersList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::action_OrdersList()
{
    QString title="Orders list";
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

    Orders_list *active_OrdersList=new Orders_list(subWindow,false);

    subWindow->setWidget(active_OrdersList);
    mdiArea->addSubWindow(subWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

MainWindow::~MainWindow()
{

}

