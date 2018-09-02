#ifndef DELEGATE_H
#define DELEGATE_H

#include "allinclude.h"

class ComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
  ComboBoxDelegate(QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  QStringList Items;

};


class ColorTextDelegate : public QItemDelegate
{
    Q_OBJECT
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem op(option);
        qDebug()<<index.data().toString();
        QPalette palette;
        QColor color=QColor(255,0,0);
        op.palette.setColor(QPalette::Text, color);
//        op.palette.setColor(QPalette::Text, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::Window, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::Highlight, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::HighlightedText, palette.color(QPalette::Base));

        QItemDelegate::paint(painter, op, index);
    }
};


#endif // DELEGATE_H
