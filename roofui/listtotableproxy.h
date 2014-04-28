#ifndef LISTTOTABLEPROXY_H
#define LISTTOTABLEPROXY_H

#include <QAbstractProxyModel>
#include "roofimagesmodel.h"

class ListToTableProxy : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit ListToTableProxy(QObject *parent = 0);
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex parent(const QModelIndex &) const;
    QModelIndex index(int row, int column, const QModelIndex&) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
signals:

public slots:
    void updateColumnByWidth(int _size);
    void updateTable();

private:
    int getColumnNum() const;
    int widgetSize;
};

#endif // LISTTOTABLEPROXY_H
