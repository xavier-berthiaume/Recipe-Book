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
  explicit QProfile(const QString &username, QObject *parent = nullptr);
  explicit QProfile(const QUuid &id, const QString &username,
                    QObject *parent = nullptr);

  QString getUsername() const;

  void setUsername(const QString &username);

  void accept(DatabaseVisitor *visitor) override;

signals:
  void usernameChanged();
};

#endif
