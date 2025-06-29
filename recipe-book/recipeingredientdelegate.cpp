#include "recipeingredientdelegate.h"
#include "recipeingredientlistmodel.h"

RecipeIngredientDelegate::RecipeIngredientDelegate(QObject *parent)
    : QAbstractItemDelegate{parent}
{}

void RecipeIngredientDelegate::drawButton(QPainter *painter,
                                          const QRect &rect,
                                          const QString &text,
                                          const QStyleOptionViewItem &option) const {

}

void RecipeIngredientDelegate::paint(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
    if (!index.isValid()) return;

    QString headerText = QString("%1, %2%3").arg(
        index.data(RecipeIngredientListModel::NameRole).toString(),
        index.data(RecipeIngredientListModel::QuantityRole).toString(),
        index.data(RecipeIngredientListModel::UnitRole).toString());

    QString description = index.data(RecipeIngredientListModel::DescriptionRole).toString();

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, option.palette.alternateBase());
    }

    QRect headerRect = option.rect.adjusted(5, 0, -100, 5);
    QRect descriptionRect = option.rect.adjusted(200, 30, 300, 5);
    QFont font;

    font.setBold(true);
    font.setPointSize(20);
    font.setFamily("Arial");

    painter->setFont(font);
    painter->drawText(headerRect, headerText, Qt::AlignLeft | Qt::AlignVCenter);

    font.setBold(false);
    font.setItalic(true);
    font.setPointSize(11);

    painter->setFont(font);
    painter->drawText(descriptionRect, description, Qt::AlignLeft | Qt::AlignTop);

    painter->restore();
}

QSize RecipeIngredientDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(300, 60);
}

bool RecipeIngredientDelegate::editorEvent(QEvent *event,
                                           QAbstractItemModel *model,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) {

    return false;
}
