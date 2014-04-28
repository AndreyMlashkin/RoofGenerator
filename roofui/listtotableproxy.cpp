#include "listtotableproxy.h"

ListToTableProxy::ListToTableProxy(QObject *parent) :
    QAbstractProxyModel(parent), widgetSize(100)
{
}

QModelIndex ListToTableProxy::mapToSource(const QModelIndex &proxyIndex) const
{
    if(!proxyIndex.isValid())
        return QModelIndex();
    int columnNum = getColumnNum();
    int realIndex = proxyIndex.row()*columnNum + proxyIndex.column();
    return createIndex(realIndex, 0);
}

QModelIndex ListToTableProxy::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(!sourceIndex.isValid())
        return QModelIndex();
    int columnNum = getColumnNum();
    return createIndex(sourceIndex.column()%columnNum, sourceIndex.column()/columnNum);
}

QModelIndex ListToTableProxy::parent(const QModelIndex &) const
{
    return QModelIndex();
}

QModelIndex ListToTableProxy::index(int row, int column, const QModelIndex&) const
{
    if(row < 0 || column < 0)
        return QModelIndex();
    RoofImage *currentRoof = NULL;
    int columnNum = getColumnNum();
    int currentIndex = row*columnNum + column;
    RoofImagesModel *source = dynamic_cast<RoofImagesModel *>(sourceModel());
    if(currentIndex < source->getRoofList().count())
        currentRoof = source->getRoofList()[currentIndex];

    return createIndex(row, column, currentRoof);
}

int ListToTableProxy::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
          return 0;
    RoofImagesModel *source = dynamic_cast<RoofImagesModel *>(sourceModel());
//    qDebug()<<" row: "<<(qRound((qreal)(source->getRoofList().count()/(getColumnNum())))+1);
    return qRound((qreal)(source->getRoofList().count()/(getColumnNum())))+1;
}

int ListToTableProxy::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
          return 0;
//    qDebug()<< "column: "<<getColumnNum();
    return getColumnNum();
}

int ListToTableProxy::getColumnNum() const
{
    RoofImagesModel *source = dynamic_cast<RoofImagesModel *>(sourceModel());
    return widgetSize/source->getBlockSize().width();
}

void ListToTableProxy::updateColumnByWidth(int _size){
    if(_size != 0 && _size != widgetSize){
        widgetSize = _size;
        emit layoutChanged();
    }
}

void ListToTableProxy::updateTable()
{
//    emit dataChanged(QModelIndex(),QModelIndex());
    emit layoutChanged();
}
