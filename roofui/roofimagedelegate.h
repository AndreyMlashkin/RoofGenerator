#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QStyledItemDelegate>

class RoofImageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    RoofImageDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &,
                   const QModelIndex &index) const;
};

#endif // LISTDELEGATE_H
