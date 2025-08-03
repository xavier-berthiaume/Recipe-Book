#ifndef PROFILELISTDELEGATE_H
#define PROFILELISTDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class ProfileListDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  explicit ProfileListDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;

signals:
  void updateEditor(const QModelIndex &index);
};

#endif // PROFILELISTDELEGATE_H
