#ifndef RECIPELISTDELEGATE_H
#define RECIPELISTDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class RecipeListDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  explicit RecipeListDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif
