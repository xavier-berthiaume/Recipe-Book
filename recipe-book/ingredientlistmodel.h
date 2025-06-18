#ifndef INGREDIENTLISTMODEL_H
#define INGREDIENTLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "qingredient.h"

class IngredientListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<QIngredient *> m_ingredients;
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        IdRole,
        CreatorRole,
    };

    explicit IngredientListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addIngredient(QIngredient *ingredient);

    void modifyIngredient(int index, const QVariant &data, int role = Qt::DisplayRole);

    void removeIngredient(int index);

public slots:
    void ingredientCreated(QIngredient *ingredient);
};

#endif // INGREDIENTLISTMODEL_H
