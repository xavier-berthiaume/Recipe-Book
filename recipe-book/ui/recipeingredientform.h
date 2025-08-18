#ifndef RECIPEINGREDIENTFORM_H
#define RECIPEINGREDIENTFORM_H

#include "abstractform.h"
#include "ingredientlistmodel.h"
#include "recipelistmodel.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QToolButton>

namespace Ui {
class RecipeIngredientForm;
}

class RecipeIngredientForm : public AbstractForm {
  Q_OBJECT

  explicit RecipeIngredientForm(QWidget *parent = nullptr);
  explicit RecipeIngredientForm(Storable *object, QWidget *parent = nullptr);

  bool validateForm() override;
  void extractFormData() override;
  void populateForm(const QVariantMap &data) override;
  void clearForm() override;
  void refreshLoadedCount();
  void initialize();

  QTabWidget *m_tabs;
  IngredientListModel *m_ingredientModel;
  RecipeListModel *m_recipeModel;
  QListView *m_ingredientList;
  QListView *m_recipeList;
  QToolButton *m_loadMoreButton;
  QDoubleSpinBox *m_quantityEdit;
  QListWidget *m_unitList;
  QLabel *m_loadedCount;
  QLabel *m_totalCount;

  Ui::RecipeIngredientForm *ui;

  int m_recipeCount = 0;
  int m_ingredientCount = 0;

public:
  static RecipeIngredientForm *createForm(QWidget *parent);
  static RecipeIngredientForm *editForm(Storable *object, QWidget *parent);

  int exec() override;

  ~RecipeIngredientForm();

public slots:
  void handleObjectsCounted(ObjectTypes type, int count);
  void handleObjectLoaded(ObjectTypes type, Storable *object);
};

#endif // RECIPEINGREDIENTFORM_H
