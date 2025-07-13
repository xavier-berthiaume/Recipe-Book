#ifndef QPROFILE_H
#define QPROFILE_H

#include "profile.h"
#include "storable.h"

class QProfile : public Storable {
  Q_OBJECT

  Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY
                 usernameChanged)

  Profile m_profile;

public:
  explicit QProfile(QObject *parent = nullptr);
  explicit QProfile(const QUuid &id, QObject *parent = nullptr);
  explicit QProfile(const QString &username, QObject *parent = nullptr);
  explicit QProfile(const Profile &profile, QObject *parent = nullptr);

  ~QProfile();

  QString getUsername() const;

  void setUsername(const QString &username);

signals:
  void usernameChanged();
};

#endif // QPROFILE_H
