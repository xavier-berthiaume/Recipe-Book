#ifndef PROFILELISTMODEL_H
#define PROFILELISTMODEL_H

#include "../models.h"
#include "genericlistmodel.h"

class ProfileListModel : public GenericListModel<QProfile> {
  Q_OBJECT

protected:
  void connectModelSignals(QProfile *model) const override;

public:
  enum Roles {
    UsernameRole = Qt::UserRole + 1,
    IdRole,
  };

  explicit ProfileListModel(QObject *parent = nullptr);

  QHash<int, QByteArray> roleNames() const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QProfile *getProfile(const QModelIndex &index) const;

  void modifyModel(int index, const QVariant &data,
                   int role = Qt::DisplayRole) override;
};
#endif
