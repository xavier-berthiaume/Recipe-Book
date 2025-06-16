#include "profilelistmodel.h"

ProfileListModel::ProfileListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int ProfileListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_profiles.size();
}

QVariant ProfileListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() && index.row() >= m_profiles.size()) return QVariant();

    QProfile *profile = m_profiles.at(index.row());

    switch(role) {
    case Roles::UsernameRole:
        return profile->getUsername();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ProfileListModel::roleNames() const {
    return {
        {Roles::UsernameRole, "Username"},
    };
}

void ProfileListModel::addProfile(QProfile *profile) {

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_profiles.append(profile);
    // Connect the profiles username changed signal to the model
    connect(profile, &QProfile::usernameChanged, this, [this, profile]() {
        int row = m_profiles.indexOf(profile);
        if (row >= 0) {
            QModelIndex index = this->index(row);
            emit dataChanged(index, index);
        }
    });
    endInsertRows();
}

void ProfileListModel::modifyProfile(int index, const QVariant &data, int role) {

    QModelIndex indx = this->index(index);
    if (!indx.isValid() || index >= m_profiles.size()) return;

    QProfile *profile = m_profiles[index];

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

void ProfileListModel::removeProfile(int index) {
    if (index < 0 || index >= m_profiles.size()) return;

    beginRemoveRows(QModelIndex(), index, index);
    m_profiles.removeAt(index);
    endRemoveRows();
}

void ProfileListModel::profileCreated(QProfile *profile) {
    profile->setParent(this);
    addProfile(profile);
    qDebug() << "Added profile to ProfileListModel with username " << profile->getUsername();
}
