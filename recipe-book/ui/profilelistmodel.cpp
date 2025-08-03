#include "profilelistmodel.h"

ProfileListModel::ProfileListModel(QObject *parent)
    : GenericListModel<QProfile>(parent) {}

// TODO IMPLEMENT ALONGSIDE SIGNALS
void ProfileListModel::connectModelSignals(QProfile *model) const {}

QHash<int, QByteArray> ProfileListModel::roleNames() const {
  return {{Roles::UsernameRole, "Username"}, {Roles::IdRole, "ID"}};
}

QVariant ProfileListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() && index.row() >= m_modelList.size())
    return QVariant();

  QProfile *profile = m_modelList.at(index.row());

  switch (role) {
  case Roles::UsernameRole:
    return profile->getUsername();

  case Roles::IdRole:
    return profile->getId();

  default:
    return QVariant();
  }
}

QProfile *ProfileListModel::getProfile(const QModelIndex &index) const {
  qDebug() << "Getting profile at index" << index.row();
  if (!index.isValid() || index.row() >= m_modelList.size()) {
    qWarning() << "Invalid index passed";
    return nullptr;
  }

  return m_modelList[index.row()];
}

void ProfileListModel::modifyModel(int index, const QVariant &data, int role) {

  QModelIndex indx = this->index(index);
  if (!indx.isValid() || index >= m_modelList.size())
    return;

  QProfile *profile = m_modelList[index];

  switch (role) {
  case ProfileListModel::UsernameRole:
    if (profile->getUsername() != data.toString()) {
      profile->setUsername(data.toString());
      emit dataChanged(indx, indx);
    }
    break;

  default:
    break;
  }
}
