#include "profilelistdelegate.h"
#include "profilelistmodel.h"

ProfileListDelegate::ProfileListDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void ProfileListDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
  QString username = index.data(ProfileListModel::UsernameRole).toString();

  painter->save();

  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  } else if (option.state & QStyle::State_MouseOver) {
    painter->fillRect(option.rect, option.palette.alternateBase());
  }

  painter->setPen(option.state & QStyle::State_Selected
                      ? option.palette.highlightedText().color()
                      : option.palette.text().color());

  QRect usernameRect = option.rect.adjusted(5, 5, -100, 5);
  QFont font;
  font.setBold(true);
  font.setPointSize(20);
  font.setFamily("Arial");

  painter->setFont(font);
  painter->drawText(usernameRect, username, Qt::AlignLeft | Qt::AlignVCenter);
}

QSize ProfileListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  return QSize(300, 60);
}
