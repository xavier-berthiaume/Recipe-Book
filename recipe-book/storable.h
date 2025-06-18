#ifndef STORABLE_H
#define STORABLE_H

#include <QObject>
#include <QUuid>

class Storable : public QObject {
    Q_OBJECT

    Q_PROPERTY(QUuid id READ getId WRITE setId NOTIFY idChanged)

protected:
    QUuid m_id;

public:
    explicit Storable(QObject *parent = nullptr);
    explicit Storable(QUuid id, QObject *parent = nullptr);

    QUuid getId() const;
    void setId(QUuid id);

signals:
    void idChanged();
};

#endif
