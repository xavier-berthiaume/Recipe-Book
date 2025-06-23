#ifndef INGREDIENTSELECTIONDELEGATE_H
#define INGREDIENTSELECTIONDELEGATE_H

#include <QAbstractItemDelegate>

class IngredientSelectionDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit IngredientSelectionDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // INGREDIENTSELECTIONDELEGATE_H
