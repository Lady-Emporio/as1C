#include "subtable.h"

Subtable::Subtable(QWidget *parent,int indexColumnToHide,int parentColumnToHide,QString parentIndex,int dateIndex) :
    BaseTable(parent),
    indexColumnToHide(indexColumnToHide),
    parentColumnToHide(parentColumnToHide),
    parentIndex(parentIndex),
    dateIndex(dateIndex)
{

}

void Subtable::action_addRow()
{
    if(modelTable!=nullptr){
        int newRow=modelTable->rowCount();
        modelTable->insertRow(newRow);
        modelTable->setData(modelTable->index(newRow,parentColumnToHide),parentIndex);
        if(dateIndex!=-1){
            modelTable->setData(modelTable->index(newRow,dateIndex),QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss"));
        }
    }else if(modelRelational!=nullptr){
        int newRow=modelRelational->rowCount();
        modelRelational->insertRow(newRow);
        modelRelational->setData(modelRelational->index(newRow,parentColumnToHide),parentIndex);
        if(dateIndex!=-1){
            modelRelational->setData(modelRelational->index(newRow,dateIndex),QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss"));
        }
    }
}

void Subtable::hideColumn()
{
    this->tableView->hideColumn(indexColumnToHide);
    this->tableView->hideColumn(parentColumnToHide);
    if(-1!=dateIndex){
       this->tableView->hideColumn(dateIndex);
    }
}
