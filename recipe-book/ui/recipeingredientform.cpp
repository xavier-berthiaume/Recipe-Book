#include "recipeingredientform.h"
#include "ingredientselectordelegate.h"
#include "ui_recipeingredientform.h"

RecipeIngredientForm::RecipeIngredientForm(QWidget *parent)
    : AbstractForm(RECIPEINGREDIENTOBJECT, parent),
      ui(new Ui::RecipeIngredientForm) {}

RecipeIngredientForm::RecipeIngredientForm(Storable *object, QWidget *parent)
    : AbstractForm(RECIPEINGREDIENTOBJECT, object, parent),
      ui(new Ui::RecipeIngredientForm) {}

RecipeIngredientForm::~RecipeIngredientForm() { delete ui; }

int RecipeIngredientForm::exec() {

  qDebug() << "Sending requests for ingredients and recipes";
  emit requestObjects(INGREDIENTOBJECT);
  emit requestObjectsCount(INGREDIENTOBJECT);
  emit requestObjects(RECIPEOBJECT);
  emit requestObjectsCount(RECIPEOBJECT);

  if (m_currentObject != nullptr) {
    QUuid ingredientId =
        qobject_cast<QRecipeIngredient *>(m_currentObject)->getIngredientId();
    ObjectTypes type = INGREDIENTOBJECT;
    if (qobject_cast<QRecipeIngredient *>(m_currentObject)->getIsRecipe()) {
      type = RECIPEOBJECT;
    }

    emit requestObject(type, ingredientId);
  }

  return AbstractForm::exec();
}

bool RecipeIngredientForm::validateForm() {
  if (m_quantityEdit->value() <= 0.0)
    return false;

  // If there's no selection in both ingredient and recipe lists
  if (!m_ingredientList->currentIndex().isValid() &&
      !m_recipeList->currentIndex().isValid())
    return false;

  // If there's no selection in the units
  if (!m_unitList->currentIndex().isValid())
    return false;

  return true;
}

void RecipeIngredientForm::extractFormData() {
  QTabWidget *selector = findChild<QTabWidget *>("tabWidget");
  QListView *activeList = selector->currentWidget()->findChild<QListView *>();
  QUuid ingredientId;

  if (selector->currentIndex() == 0) {
    qDebug() << "Current list index" << activeList->currentIndex().row();
    ingredientId =
        m_ingredientModel
            ->data(activeList->currentIndex(), IngredientListModel::IdRole)
            .toUuid();
    m_data["isRecipe"] = false;
  } else if (selector->currentIndex() == 1) {
    ingredientId =
        m_recipeModel->data(activeList->currentIndex(), RecipeListModel::IdRole)
            .toUuid();
    m_data["isRecipe"] = true;
  }

  m_data["ingredientId"] = ingredientId;
  m_data["unit"] = m_unitList->currentItem()->data(Qt::UserRole);
  m_data["quantity"] = m_quantityEdit->value();
}

void RecipeIngredientForm::populateForm(const QVariantMap &data) {
  m_quantityEdit->setValue(data["quantity"].toDouble());

  Units unit = data["unit"].value<Units>();
  for (int i = 0; i < m_unitList->count(); ++i) {
    QListWidgetItem *item = m_unitList->item(i);
    if (item->data(Qt::UserRole).value<Units>() == unit) {
      m_unitList->setCurrentItem(item);
      break;
    }
  }
}

void RecipeIngredientForm::clearForm() {
  m_ingredientList->clearSelection();
  m_recipeList->clearSelection();

  m_quantityEdit->setValue(0.0);
  m_unitList->clearSelection();
}

void RecipeIngredientForm::refreshLoadedCount() {
  int loadCount = 0;
  int totalCount = 0;

  if (m_tabs->currentIndex() == 0) {
    loadCount = m_ingredientModel->rowCount();
    totalCount = m_ingredientCount;
  } else {
    loadCount = m_recipeModel->rowCount();
    totalCount = m_recipeCount;
  }

  m_loadedCount->setText(QString::number(loadCount));
  m_totalCount->setText(QString::number(totalCount));
}

void RecipeIngredientForm::initialize() {
  ui->setupUi(this);

  m_ingredientModel = new IngredientListModel(this);
  m_recipeModel = new RecipeListModel(this);

  m_loadMoreButton = findChild<QToolButton *>("loadMoreButton");

  m_ingredientList = findChild<QListView *>("ingredientsView");
  m_recipeList = findChild<QListView *>("recipesView");
  m_quantityEdit = findChild<QDoubleSpinBox *>("quantityEdit");
  m_unitList = findChild<QListWidget *>("unitList");

  m_quantityEdit->setMinimum(0.0);

  m_ingredientList->setModel(m_ingredientModel);
  m_recipeList->setModel(m_recipeModel);
  m_ingredientList->setItemDelegate(new IngredientSelectorDelegate(this));
  m_recipeList->setItemDelegate(new IngredientSelectorDelegate(this));

  m_loadedCount = findChild<QLabel *>("loadedCountIndicator");
  m_totalCount = findChild<QLabel *>("totalCountIndicator");

  m_tabs = findChild<QTabWidget *>("tabWidget");
  m_tabs->setCurrentIndex(0);

  QMap<QString, Units> units = QRecipeIngredient::getUnitList();
  m_unitList->clear();

  for (auto it = units.constBegin(); it != units.constEnd(); ++it) {
    QListWidgetItem *item = new QListWidgetItem(it.key());
    item->setData(Qt::UserRole, QVariant::fromValue(it.value()));
    m_unitList->addItem(item);
  }

  connect(this, &QDialog::accepted, [this]() {
    if (!validateForm())
      return;

    extractFormData();
    if (isEditMode()) {
      qDebug() << "Submitted form to update recipe ingredient"
               << m_data["id"].toString();
      emit updateRequested(objectType(), m_currentObject, m_data);
    } else {
      qDebug() << "Submitted form to create new recipe ingredient";
      emit createRequested(objectType(), m_data);
    }
  });

  connect(this, &QDialog::rejected, [this]() { clearForm(); });
}

RecipeIngredientForm *RecipeIngredientForm::createForm(QWidget *parent) {
  RecipeIngredientForm *form = new RecipeIngredientForm(parent);
  form->initialize();

  return form;
}

RecipeIngredientForm *RecipeIngredientForm::editForm(Storable *object,
                                                     QWidget *parent) {
  RecipeIngredientForm *form = new RecipeIngredientForm(object, parent);
  form->initialize();

  QRecipeIngredient *ingredient = qobject_cast<QRecipeIngredient *>(object);
  QVariantMap data;
  data["id"] = ingredient->getId();
  data["ingredientId"] = ingredient->getIngredientId();
  data["quantity"] = ingredient->getQuantity();
  data["unit"] = ingredient->getUnit();
  data["isRecipe"] = ingredient->getIsRecipe();
  form->populateForm(data);

  return form;
}

void RecipeIngredientForm::handleObjectsCounted(ObjectTypes type, int count) {
  switch (type) {
  case INGREDIENTOBJECT:
    qDebug() << "Received ingredient count" << count;
    m_ingredientCount = count;
    break;

  case RECIPEOBJECT:
    qDebug() << "Received recipe count" << count;
    m_recipeCount = count;
    break;

  default:
    break;
  }
}

void RecipeIngredientForm::handleObjectLoaded(ObjectTypes type,
                                              Storable *object) {
  switch (type) {
  case INGREDIENTOBJECT:
    qDebug() << "Loaded ingredient" << object->getId().toString();
    m_ingredientModel->addModel(qobject_cast<QIngredient *>(object));
    break;

  case RECIPEOBJECT:
    qDebug() << "Loaded recipe" << object->getId().toString();
    m_recipeModel->addModel(qobject_cast<QRecipe *>(object));
    break;

  default:
    break;
  }
}
