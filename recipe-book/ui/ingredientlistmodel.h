#ifndef INGREDIENTLISTMODEL_H
#define INGREDIENTLISTMODEL_H

#include "../models.h"
#include "genericlistmodel.h"

class IngredientListModel : public GenericListModel<QIngredient> {
  Q_OBJECT

protected:
  void connectModelSignals(QIngredient *model) const override;

public:
  enum Roles { NameRole = Qt::UserRole + 1, DescriptionRole, IdRole };

  explicit IngredientListModel(QObject *parent = nullptr);

  QHash<int, QByteArray> roleNames() const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QIngredient *getIngredient(const QModelIndex &index) const;

  void modifyModel(int index, const QVariant &data,
                   int role = Qt::DisplayRole) override;

  void clearModel();
};

#endif
