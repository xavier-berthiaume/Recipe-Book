#include "recipeingredientdelegate.h"
#include "recipeingredientlistmodel.h"

#include <QApplication>
#include <QMouseEvent>

RecipeIngredientDelegate::RecipeIngredientDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {}

void RecipeIngredientDelegate::drawButton(
    QPainter *painter, const QRect &rect, const QString &text,
    const QStyleOptionViewItem &option) const {
  QStyleOptionButton button;
  button.rect = rect;
  button.text = text;
  button.state = QStyle::State_Enabled;

  if (rect.contains(m_lastMousePos)) {
    button.state |= QStyle::State_MouseOver;
  }

  QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

void RecipeIngredientDelegate::paint(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  if (!index.isValid())
    return;

  QString headerText =
      QString("%1 - %2%3")
          .arg(index.data(RecipeIngredientListModel::NameRole).toString(),
               index.data(RecipeIngredientListModel::QuantityRole).toString(),
               index.data(RecipeIngredientListModel::UnitRole).toString());

  QString description =
      index.data(RecipeIngredientListModel::DescriptionRole).toString();

  painter->save();

  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  } else if (option.state & QStyle::State_MouseOver) {
    painter->fillRect(option.rect, option.palette.alternateBase());
  }

  QRect headerRect = option.rect.adjusted(5, 0, -100, 5);
  QRect descriptionRect = option.rect.adjusted(200, 30, 300, 5);
  QFont font;

  font.setBold(true);
  font.setPointSize(11);
  font.setFamily("Arial");

  painter->setFont(font);
  painter->drawText(headerRect, headerText, Qt::AlignLeft | Qt::AlignVCenter);

  font.setBold(false);
  font.setItalic(true);
  font.setPointSize(11);

  painter->setFont(font);
  painter->drawText(descriptionRect, description, Qt::AlignLeft | Qt::AlignTop);

  if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver)) {
    const int buttonWidth = 70;
    const int buttonHeight = 18;
    const int buttonSpacing = 15;
    const int buttonsRightMargin = 15;

    // Calculate button positions
    int rightEdge = option.rect.right() - buttonsRightMargin;
    QRect editButtonRect(rightEdge - buttonWidth,
                         option.rect.center().y() - buttonHeight / 2,
                         buttonWidth, buttonHeight);

    // Save button positions for mouse events
    ButtonRects rects = ButtonRects();
    rects.editButton = editButtonRect;
    m_buttonRects[index.row()] = rects;

    // Draw buttons
    drawButton(painter, editButtonRect, "Edit", option);
  } else {
    m_buttonRects.remove(index.row());
  }

  painter->restore();
}

QSize RecipeIngredientDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  return QSize(300, 20);
}

bool RecipeIngredientDelegate::editorEvent(QEvent *event,
                                           QAbstractItemModel *model,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) {
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    m_lastMousePos = mouseEvent->pos();
    emit updateEditor(index);
  } else if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

    if (m_buttonRects.contains(index.row())) {
      ButtonRects rects = m_buttonRects[index.row()];

      if (rects.editButton.contains(mouseEvent->pos())) {
        emit editClicked(index);
        return true;
      }
    }
  }

  return QStyledItemDelegate::editorEvent(event, model, option, index);
}
