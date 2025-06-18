#include "ingredientlistdelegate.h"
#include "ingredientlistmodel.h"

#include <QApplication>
#include <QMouseEvent>

IngredientListDelegate::IngredientListDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void IngredientListDelegate::paint(QPainter *painter,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
    if (!index.isValid()) return;

    QString name = index.data(IngredientListModel::NameRole).toString();
    QString description = index.data(IngredientListModel::DescriptionRole).toString();
    QString author = QString("Created by: %1").arg(index.data(IngredientListModel::CreatorRole).value<QProfile *>()->getUsername());

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, option.palette.alternateBase());
    }

    painter->setPen(option.state & QStyle::State_Selected ?
                        option.palette.highlightedText().color() :
                        option.palette.text().color());

    QRect nameRect = option.rect.adjusted(5, 0, -100, 5);
    QRect descriptionRect = option.rect.adjusted(200, 30, 300, 5);
    QRect authorRect = option.rect.adjusted(200, 10, 300, 5);
    QFont font;

    font.setBold(true);
    font.setPointSize(20);
    font.setFamily("Arial");

    painter->setFont(font);
    painter->drawText(nameRect, name, Qt::AlignLeft | Qt::AlignVCenter);

    font.setBold(false);
    font.setItalic(true);
    font.setPointSize(11);

    painter->setFont(font);
    painter->drawText(descriptionRect, description, Qt::AlignLeft | Qt::AlignTop);

    font.setBold(false);
    font.setItalic(false);
    font.setPointSize(11);

    painter->setFont(font);
    painter->drawText(authorRect, author, Qt::AlignLeft | Qt::AlignTop);

    font.setBold(false);
    font.setItalic(false);
    font.setPointSize(11);
    font.setFamily("Canterell");

    painter->setFont(font);
    if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver)) {
        const int buttonWidth = 80;
        const int buttonHeight = 40;
        const int buttonSpacing = 15;
        const int buttonsRightMargin = 15;

        // Calculate button positions
        int rightEdge = option.rect.right() - buttonsRightMargin;
        QRect editButtonRect(rightEdge - buttonWidth, option.rect.center().y() - buttonHeight/2,
                             buttonWidth, buttonHeight);
        QRect deleteButtonRect(editButtonRect.left() - buttonWidth - buttonSpacing,
                               editButtonRect.top(), buttonWidth, buttonHeight);

        // Save button positions for mouse events
        ButtonRects rects = ButtonRects();
        rects.deleteButton = deleteButtonRect;
        rects.editButton = editButtonRect;
        m_buttonRects[index.row()] = rects;

        // Draw buttons
        drawButton(painter, editButtonRect, "Edit", option);
        drawButton(painter, deleteButtonRect, "Delete", option);
    } else {

        m_buttonRects.remove(index.row());
    }

    painter->restore();
}

QSize IngredientListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)

    return QSize(300, 60);
}

bool IngredientListDelegate::editorEvent(QEvent *event,
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
            } else if (rects.deleteButton.contains(mouseEvent->pos())) {
                emit deleteClicked(index);
                return true;
            }
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void IngredientListDelegate::drawButton(QPainter *painter, const QRect &rect,
                                        const QString &text, const QStyleOptionViewItem &option) const {
    QStyleOptionButton button;
    button.rect = rect;
    button.text = text;
    button.state = QStyle::State_Enabled;

    if (rect.contains(m_lastMousePos)) {
        button.state |= QStyle::State_MouseOver;
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}
