#ifndef PROFILELISTMODEL_H
#define PROFILELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "qprofile.h"

class ProfileListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<QProfile *> m_profiles;
public:
    enum Roles {
        UsernameRole = Qt::UserRole + 1
    };

    explicit ProfileListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addProfile(QProfile *profile);

    void modifyProfile(int index, const QVariant &data, int role = Qt::DisplayRole);

    void removeProfile(int index);

public slots:
    void profileCreated(QProfile *profile);
};

#endif // PROFILELISTMODEL_H
