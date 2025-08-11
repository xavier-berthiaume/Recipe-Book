#include "recipelistdelegate.h"
#include "recipelistmodel.h"

RecipeListDelegate::RecipeListDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void RecipeListDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
  QString name = index.data(RecipeListModel::NameRole).toString();

  painter->save();

  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  } else if (option.state & QStyle::State_MouseOver) {
    painter->fillRect(option.rect, option.palette.alternateBase());
  }

  painter->setPen(option.state & QStyle::State_Selected
                      ? option.palette.highlightedText().color()
                      : option.palette.text().color());

  QRect nameRect = option.rect.adjusted(5, 5, -100, 5);
  QFont font;
  font.setBold(true);
  font.setPointSize(16);
  font.setFamily("Arial");

  painter->setFont(font);
  painter->drawText(nameRect, name, Qt::AlignLeft | Qt::AlignVCenter);

  painter->restore();
}

QSize RecipeListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  return QSize(300, 60);
}
