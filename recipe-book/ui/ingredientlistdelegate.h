#ifndef INGREDIENTLISTDELEGATE_H
#define INGREDIENTLISTDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <qstyleoption.h>

class IngredientListDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  explicit IngredientListDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif
