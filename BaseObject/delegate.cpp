#include "delegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
:QItemDelegate(parent)
{
}


QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  editor->setEditable(true);
  editor->addItems(Items);
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  comboBox->setEditText(index.model()->data(index).toString());
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

QWidget *DelegateForCall::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    0" _id INTEGER PRIMARY KEY NOT NULL, "
//    1" _phone INTEGER REFERENCES phone(_id) ON UPDATE CASCADE NOT NULL, "
//    2" _vinCar TEXT, "
//    3" _code_dealer TEXT, "
//    4" _activePhone TEXT, "
//    5" _blockCar TEXT, "
//    6" _dateCar TEXT, "
//    7" _dealerNameAndOpen TEXT, "
//    8" _dealerLastCall TEXT, "
//    9" _modelCar TEXT, "
//   10" _optionCar TEXT, "
//   11" _colorCar TEXT, "
//   12" _dateTalk TEXT, "
//   13" _colorTalk TEXT CHECK(_colorTalk in ('','Красный','Зеленый','Синий','Коричневый','Желтый','Фиолетовый') ), "
//   14" _commentTalk TEXT "
    if(12==index.column()){
        QString now=Settings::getSqlTime();
        QSqlTableModel *parentModel=(QSqlTableModel*)index.model();
        parentModel->setData(index,now);
        return nullptr;
    }else if(13==index.column()){
        QComboBox* editor = new QComboBox(parent);
        editor->setEditable(true);
        QStringList Items;
        Items<<""<<"Красный"<<"Зеленый"<<"Синий"<<"Коричневый"<<"Желтый"<<"Фиолетовый";
        editor->addItems(Items);
        return editor;
    }else{
        return new QLineEdit(parent);
    }
    return nullptr;
}
