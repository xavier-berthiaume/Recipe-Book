#include "recipeingredientlistdelegate.h"
#include "recipeingredientlistmodel.h"

RecipeIngredientListDelegate::RecipeIngredientListDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void RecipeIngredientListDelegate::paint(QPainter *painter,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  QString name = index.data(RecipeIngredientListModel::NameRole).toString();
  double quantity =
      index.data(RecipeIngredientListModel::QuantityRole).toDouble();
  QString unit = QRecipeIngredient::unitToString(
      index.data(RecipeIngredientListModel::UnitRole).value<Units>());

  painter->save();

  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  } else if (option.state & QStyle::State_MouseOver) {
    painter->fillRect(option.rect, option.palette.alternateBase());
  }

  painter->setPen(option.state & QStyle::State_Selected
                      ? option.palette.highlightedText().color()
                      : option.palette.text().color());

  QRect infoRect = option.rect.adjusted(5, 0, -50, 0);
  QFont font;
  font.setBold(true);
  font.setPointSize(12);
  font.setFamily("Arial");

  painter->setFont(font);

  painter->drawText(infoRect,
                    QString("%1 %2%3").arg(name).arg(quantity).arg(unit),
                    Qt::AlignLeft | Qt::AlignVCenter);

  painter->restore();
}

QSize RecipeIngredientListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  return QSize(300, 60);
}
