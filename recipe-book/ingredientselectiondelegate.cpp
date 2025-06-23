#include "ingredientselectiondelegate.h"
#include "ingredientlistmodel.h"

#include <QPainter>

IngredientSelectionDelegate::IngredientSelectionDelegate(QObject *parent)
    : QAbstractItemDelegate{parent}
{}

void IngredientSelectionDelegate::paint(QPainter *painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
    if (!index.isValid()) return;

    QString name = index.data(IngredientListModel::NameRole).toString();
    QString description = index.data(IngredientListModel::DescriptionRole).toString();

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, option.palette.alternateBase());
    }

    painter->setPen(option.state & QStyle::State_Selected ?
                        option.palette.highlightedText().color() :
                        option.palette.text().color());

    QRect nameRect = option.rect.adjusted(5, 0, -100, 5);
    QRect descriptionRect = option.rect.adjusted(200, 30, 300, 5);
    QFont font;

    font.setBold(true);
    font.setPointSize(20);
    font.setFamily("Arial");

    painter->setFont(font);
    painter->drawText(nameRect, name, Qt::AlignLeft | Qt::AlignVCenter);

    font.setBold(false);
    font.setItalic(true);
    font.setPointSize(11);

    painter->setFont(font);
    painter->drawText(descriptionRect, description, Qt::AlignLeft | Qt::AlignTop);

    painter->restore();
}

QSize IngredientSelectionDelegate::sizeHint(const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)

    return QSize(300, 60);
}
