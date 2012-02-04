#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H

#include <QtGui>

class ListviewDelegate : public QStyledItemDelegate
{
public:
    ListviewDelegate();
    virtual ~ListviewDelegate();

    enum datarole {headerTextRole = Qt::UserRole + 100,subHeaderTextrole = Qt::UserRole+101,IconRole = Qt::UserRole+102};

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;

};

#endif // LISTVIEWDELEGATE_H
