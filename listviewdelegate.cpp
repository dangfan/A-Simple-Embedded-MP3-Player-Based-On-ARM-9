#include "listviewdelegate.h"

ListviewDelegate::ListviewDelegate()
{
    // TODO Auto-generated constructor stub

}

ListviewDelegate::~ListviewDelegate()
{
    // TODO Auto-generated destructor stub
}

//alocate each item size in listview.
QSize ListviewDelegate::sizeHint(const QStyleOptionViewItem &  option ,
                                 const QModelIndex & index) const
{
    QIcon icon = qvariant_cast<QIcon>(index.data(IconRole));
    QSize iconsize = icon.actualSize(option.decorationSize);
    QFont font = QApplication::font();
    font.setPointSize(15);
    QFontMetrics fm(font);
    return(QSize(iconsize.width(),iconsize.height()+fm.height() +8 ));
}
void ListviewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);

    painter->save();

    QFont font = QApplication::font();
    QFont SubFont = QApplication::font();
    //font.setPixelSize(font.weight()+);
    font.setBold(true);
    font.setPointSize(15);
    SubFont.setPointSize(12);
    QFontMetrics fm(font);

    QIcon icon = qvariant_cast<QIcon>(index.data(IconRole));
    QString headerText = qvariant_cast<QString>(index.data(headerTextRole));
    QString subText = qvariant_cast<QString>(index.data(subHeaderTextrole));

    QSize iconsize = icon.actualSize(option.decorationSize);

    QRect headerRect = option.rect;
    QRect subheaderRect = option.rect;
    QRect iconRect = subheaderRect;

    iconRect.setRight(iconsize.width()+30);
    iconRect.setTop(iconRect.top()+8);
    headerRect.setLeft(iconRect.right());
    subheaderRect.setLeft(iconRect.right());
    if (subText.isEmpty())
        headerRect.setTop(headerRect.top()+16);
    else
        headerRect.setTop(headerRect.top()+5);
    headerRect.setBottom(headerRect.top()+fm.height());

    subheaderRect.setTop(headerRect.bottom()+2);

    painter->drawPixmap(QPoint(iconRect.left()+iconsize.width()/2+2,iconRect.top()+iconsize.height()/2+3),icon.pixmap(iconsize.width(),iconsize.height()));

    painter->setFont(font);
    painter->drawText(headerRect,headerText);

    painter->setFont(SubFont);
    painter->drawText(subheaderRect.left(),subheaderRect.top()+17,subText);
    painter->restore();

}
