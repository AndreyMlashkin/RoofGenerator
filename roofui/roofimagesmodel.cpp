#include "roofimagesmodel.h"
#include <QDebug>
#include <QtGlobal>

RoofImagesModel::RoofImagesModel(QObject *parent) :
    QAbstractListModel(parent), blockSize(150, 100), state(TABLE)
{
}

int RoofImagesModel::rowCount(const QModelIndex &) const
{
        return roofList.count();
}

int RoofImagesModel::columnCount(const QModelIndex &) const
{
      return 1;
}

QVariant RoofImagesModel::data(const QModelIndex&, int ) const
{
    return QVariant();
}

QModelIndex RoofImagesModel::index(int row, int column, const QModelIndex&) const
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
    emit dataChanged(QModelIndex(), QModelIndex());
    emit layoutChanged();
}

void RoofImagesModel::clearAll()
{
    roofList.clear();
    emit dataChanged(QModelIndex(), QModelIndex());
    emit layoutChanged();
}

int RoofImagesModel::realIndex(int row, int column) const
{
    return row + column;
}
QVector<RoofImage *> RoofImagesModel::getRoofList() const
{
    return roofList;
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

