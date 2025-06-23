#ifndef QRECIPEINGREDIENT_H
#define QRECIPEINGREDIENT_H

#include <QObject>

#include "qingredient.h"

class QRecipeIngredient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QIngredient *m_ingredient READ getIngredient WRITE setIngredient NOTIFY ingredientChanged)
    Q_PROPERTY(QString m_quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(QString m_unit READ getUnit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(bool m_isRecipe READ getIsRecipe WRITE setIsRecipe NOTIFY isRecipeChanged)

    QIngredient *m_ingredient;
    QString m_quantity;
    QString m_unit;
    bool m_isRecipe = false;

    void setUnit(const QString &unit);

public:
    enum Units {
        Kilograms,
        Grams,
        Milligrams,
        Liters,
        Centiliters,
        Milliliters,
        Gallons,
        Pints,
        Cups,
        Tablespoons,
        Teaspoons
    };

    explicit QRecipeIngredient(QIngredient *ingredient,
                                const QString &quantity,
                                Units unit,
                                QObject *parent = nullptr);

    QIngredient *getIngredient() const;
    QString getQuantity() const;
    QString getUnit() const;
    bool getIsRecipe() const;

    void setIngredient(QIngredient *ingredient);
    void setQuantity(const QString &quantity);
    void setUnit(Units unit);
    void setIsRecipe(bool isRecipe);

    void toggleIsRecipe();

    static QString unitToString(Units unit);

signals:
    void ingredientChanged();
    void quantityChanged();
    void unitChanged();
    void isRecipeChanged();
};

#endif // QRECIPEINGREDIENT_H
