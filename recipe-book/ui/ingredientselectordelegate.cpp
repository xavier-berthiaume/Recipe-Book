#include "ingredientselectordelegate.h"
#include "ingredientlistmodel.h"

IngredientSelectorDelegate::IngredientSelectorDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void IngredientSelectorDelegate::paint(QPainter *painter,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
  QString name = index.data(IngredientListModel::NameRole).toString();

  painter->save();

  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  } else if (option.state & QStyle::State_MouseOver) {
    painter->fillRect(option.rect, option.palette.alternateBase());
  }

  painter->setPen(option.state & QStyle::State_Selected
                      ? option.palette.highlightedText().color()
                      : option.palette.text().color());

  QRect nameRect = option.rect.adjusted(5, 0, -100, 0);
  QFont font;
  font.setBold(false);
  font.setPointSize(12);
  font.setFamily("Arial");

  painter->setFont(font);
  painter->drawText(nameRect, name, Qt::AlignLeft | Qt::AlignVCenter);

  painter->restore();
}

QSize IngredientSelectorDelegate::sizeHint(const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  return QSize(300, 25);
}
