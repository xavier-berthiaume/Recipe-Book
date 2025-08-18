#ifndef RECIPEINGREDIENTLISTDELEGATE_H
#define RECIPEINGREDIENTLISTDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class RecipeIngredientListDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  explicit RecipeIngredientListDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif
