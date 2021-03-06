#include "roofimagedelegate.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QApplication>
#include "RoofImagesModel.h"
#include "roofimage.h"

void RoofImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    RoofImage* roof = reinterpret_cast<RoofImage*>(index.internalPointer());
    if (roof && !roof->getImage()->isNull()){
        painter->drawImage(option.rect, *(roof->getImage()));
        painter->drawText(option.rect, roof->getRawString());
        if(option.state.testFlag(QStyle::State_Selected)){
            painter->drawRoundRect(option.rect);
        }
//        QApplication::style()->drawControl(QStyle::CE_HeaderLabel, &option, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize RoofImageDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex &index) const
{
    if(!index.isValid())
        return QSize(150,100);
    QAbstractItemModel* tmp = const_cast<QAbstractItemModel*>(index.model());
    RoofImagesModel *model = qobject_cast<RoofImagesModel*>(tmp);
    if(model)
        return model->getBlockSize();
    else
        return QSize(150,100);
}
