#ifndef INGREDIENTSELECTORDELEGATE_H
#define INGREDIENTSELECTORDELEGATE_H

#include <QPainter>
#include <QStyleOption>
#include <QStyledItemDelegate>

class IngredientSelectorDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  explicit IngredientSelectorDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif
