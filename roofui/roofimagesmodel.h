#ifndef ROOFIMAGESMODEL_H
#define ROOFIMAGESMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QVariant>
#include <QDebug>
#include "roofimage.h"

class RoofImagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum allState{LIST, TABLE};

    explicit RoofImagesModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;


    void addItem(RoofImage *newItem);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

    allState getState() const;
    void setState(const allState &value);

    QSize getBlockSize() const;

public slots:
    void changeMode();
    void updateColumnByWidth(int _size);

private:
    int realIndex(int row, int column) const;

private:
    const QSize blockSize;
    int widgetSize;
    int columnNum;
    allState state;

    QVector <RoofImage *> roofList;
};

#endif // ROOFIMAGESMODEL_H
