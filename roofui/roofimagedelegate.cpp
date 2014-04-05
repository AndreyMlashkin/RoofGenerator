#include "roofimagedelegate.h"
#include <QPainter>
#include <QDebug>
#include "RoofImagesModel.h"
#include "roofimage.h"

void RoofImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    RoofImage* roof = reinterpret_cast<RoofImage*>(index.internalPointer());
    if (roof) {
        painter->drawImage(option.rect, *(roof->getImage()));
//        painter->drawText(option.rect, QString::number(index.row()+1)+QString(" ")+QString::number(option.state, 2));
        if(option.state.testFlag(QStyle::State_Selected)){
            painter->drawRoundRect(option.rect);
        }
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize RoofImageDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex &index) const
{
    QAbstractItemModel* tmp = const_cast<QAbstractItemModel*>(index.model());
    RoofImagesModel *model = qobject_cast<RoofImagesModel*>(tmp);
    if(model)
        return model->getBlockSize();
    else
        return QSize(150,100);
}
