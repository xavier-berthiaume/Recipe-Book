#ifndef INGREDIENTLISTDELEGATE_H
#define INGREDIENTLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class IngredientListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    struct ButtonRects {
        QRect deleteButton;
        QRect editButton;
    };

    void drawButton(QPainter *painter,
                    const QRect &rect,
                    const QString &text,
                    const QStyleOptionViewItem &option) const;
    mutable QMap<int, ButtonRects> m_buttonRects;
    QPoint m_lastMousePos;
    int m_hoveredRow;

public:
    explicit IngredientListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index) override;

signals:
    void editClicked(const QModelIndex &index);
    void deleteClicked(const QModelIndex &index);
    void updateEditor(const QModelIndex &index);
};

#endif // INGREDIENTLISTDELEGATE_H
