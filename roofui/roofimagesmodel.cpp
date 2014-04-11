#include "roofimagesmodel.h"
#include <QDebug>
#include <QtGlobal>

RoofImagesModel::RoofImagesModel(QObject *parent) :
    QAbstractListModel(parent), blockSize(100, 150), columnNum(5), state(TABLE)
{
}

int RoofImagesModel::rowCount(const QModelIndex &) const
{
    if(state == LIST)
        return roofList.count();
    else
        return qRound((qreal)(roofList.count()/(columnNum)))+1;
}

int RoofImagesModel::columnCount(const QModelIndex &) const
{
      return columnNum;
}

QVariant RoofImagesModel::data(const QModelIndex &index, int ) const
{
    int currentIndex = realIndex(index.row(), index.column());
    if(index.isValid() && currentIndex<roofList.count()){
        RoofImage *currentRoof = roofList[currentIndex];
        QVariant var;
        var.setValue(*currentRoof);
        return var;
    }else
        return QVariant();
}

QModelIndex RoofImagesModel::index(int row, int column, const QModelIndex &parent) const
{
    RoofImage *currentRoof = NULL;
    int currentIndex = realIndex(row, column);
    if(currentIndex < roofList.count())
        currentRoof = roofList[currentIndex];

    return createIndex(row, column, currentRoof);
}

void RoofImagesModel::addItem(RoofImage *newItem)
{
    roofList.append(newItem);
    dataChanged(QModelIndex(), QModelIndex());
     emit layoutChanged();
}

void RoofImagesModel::changeMode()
{
    if(state == LIST){
        state = TABLE;
        columnNum = widgetSize/blockSize.width();
    }else{
        state = LIST;
        columnNum = 1;
    }
    emit layoutChanged();
}

void RoofImagesModel::updateColumnByWidth(int _size){
    if(_size != 0 && _size != widgetSize){
        widgetSize = _size;
        if(state == TABLE){
            columnNum = widgetSize/blockSize.width();
            emit layoutChanged();
        }
    }
}

int RoofImagesModel::realIndex(int row, int column) const
{
    return row*columnNum + column;
}
QSize RoofImagesModel::getBlockSize() const
{
    return blockSize;
}


RoofImagesModel::allState RoofImagesModel::getState() const
{
    return state;
}

void RoofImagesModel::setState(const allState &value)
{
    state = value;
}

