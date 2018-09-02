#include "call.h"

TableModelForCall::TableModelForCall(QObject *parent,QSqlDatabase db) : QSqlTableModel(parent,db)
{
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant TableModelForCall::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::BackgroundColorRole){
        if(QSqlTableModel::data(this->index(idx.row(), 10)).toString() == "Красный"){
            return QColor(Qt::red);
        }
    } else if(role == Qt::DisplayRole){
        return QSqlTableModel::data(idx);
    }
    return QVariant();
}

void TableModelForCall::rowsInserted(const QModelIndex &parent, int start, int end)
{
    qDebug()<<"new row TableModelForCall"<<parent<<start<<end;
}

void Call::makeGui()
{
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    this->setLayout(mainLayout);

    modelCall=new TableModelForCall(this,Settings::S()->_db);
    modelCall->setTable("calls");
    modelCall->setFilter("_phone='"+phoneIndex+"'");

    QMenuBar * mainBar=new QMenuBar(this);
    mainLayout->setMenuBar(mainBar);
    mainBar->addAction("New row",this,SLOT(action_NewRow()));
    mainBar->addAction("Refresh",this,SLOT(action_Refresh()));
    tableView=new QTableView(this);
    mainLayout->addWidget(tableView);

    tableView->setModel(modelCall);
    if(!modelCall->select()){
        QMessageBox msgBox;
        msgBox.setText("Пробела с select call\n\n"+Settings::S()->_db.lastError().text()+" |\n "+modelCall->lastError().text());
        msgBox.exec();
        return;
    }
    tableView->hideColumn(indexColumnToHide);
    tableView->hideColumn(parentColumnToHide);
    tableView->setSortingEnabled(true);

    tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *   removeAct = new QAction("remove row",this);
    tableView->addAction(removeAct);
    connect(removeAct, SIGNAL(triggered()), this, SLOT(delete_row()));
}

Call::Call(QWidget *parent, QString phoneIndex, int indexColumnToHide, int parentColumnToHide, int commentIndex) :
    QWidget(parent),
    phoneIndex(phoneIndex),
    indexColumnToHide(indexColumnToHide),
    parentColumnToHide(parentColumnToHide),
    commentIndex(commentIndex)
{
    makeGui();
}

void Call::action_NewRow()
{
    int newRow=modelCall->rowCount();
    modelCall->insertRow(newRow);
    modelCall->setData(modelCall->index(newRow,parentColumnToHide),phoneIndex);
    modelCall->setData(modelCall->index(newRow,commentIndex),"");
}

void Call::action_Refresh()
{
    if(!modelCall->select()){
        QMessageBox msgBox;
        msgBox.setText("Пробела с select call\n\n"+Settings::S()->_db.lastError().text()+" |\n "+modelCall->lastError().text());
        msgBox.exec();
        return;
    }
}

void Call::delete_row()
{
    QModelIndex model_index=tableView->currentIndex();
    if(model_index.column()!=-1 or model_index.row()!=-1){
        QMap<int, QVariant> dataItem=modelCall->itemData(model_index);
        const QAbstractItemModel *itemModel = model_index.model();
        if (nullptr == itemModel)
        {
            return;
        }
        int row=model_index.row();
        QString text;
        for (int i = 0; i < modelCall->columnCount(); ++i)
        {
            text+="column "+QString("").setNum(i)+" :"+ modelCall->data(itemModel->index(model_index.row(),i),i).toString()+" \n";
        }
        QMessageBox msgBox;
        msgBox.setText("Need delete row?");
        msgBox.setInformativeText(text);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                modelCall->removeRow(row);
                break;
        }
    }
}
