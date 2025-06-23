#ifndef QINGREDIENT_H
#define QINGREDIENT_H

#include <QObject>

#include "ingredient.h"
#include "qprofile.h"
#include "storable.h"

class QIngredient : public Storable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QProfile *m_creator READ getCreator WRITE setCreator NOTIFY creatorChanged)

    Ingredient m_ingredient;

protected:
    QProfile *m_creator;

public:
    explicit QIngredient(QObject *parent = nullptr);
    explicit QIngredient(QUuid id, QObject *parent = nullptr);
    explicit QIngredient(const QString &name, const QString &description, QObject *parent = nullptr);
    explicit QIngredient(const Ingredient &ingredient, QObject *parent = nullptr);

    ~QIngredient();

    QString getName() const;
    QString getDescription() const;
    QProfile *getCreator() const;

    void setName(const QString &name);
    void setDescription(const QString &decsription);
    void setCreator(QProfile *creator);

signals:
    void nameChanged();
    void descriptionChanged();
    void creatorChanged();
};

#endif // QINGREDIENT_H
