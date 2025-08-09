#include "ingredientform.h"
#include "ui_ingredientform.h"

IngredientForm::IngredientForm(QWidget *parent)
    : AbstractForm(INGREDIENTOBJECT, parent), ui(new Ui::IngredientForm) {}

IngredientForm::IngredientForm(Storable *object, QWidget *parent)
    : AbstractForm(INGREDIENTOBJECT, object, parent),
      ui(new Ui::IngredientForm) {}

IngredientForm::~IngredientForm() { delete ui; }

void IngredientForm::initialize() {
  ui->setupUi(this);

  m_nameEdit = findChild<QLineEdit *>("nameEdit");
  m_descriptionEdit = findChild<QPlainTextEdit *>("descriptionEdit");

  connect(this, &QDialog::accepted, [this]() {
    if (!validateForm())
      return;

    extractFormData();
    if (isEditMode()) {
      qDebug() << "Submitted form to update ingredient"
               << m_data["id"].toString();
      emit updateRequested(objectType(), m_currentObject, m_data);
    } else {
      qDebug() << "Submitted form to create new ingredient";
      emit createRequested(objectType(), m_data);
    }
  });

  connect(this, &QDialog::rejected, [this]() { clearForm(); });
}

IngredientForm *IngredientForm::createForm(QWidget *parent) {
  IngredientForm *form = new IngredientForm(parent);
  form->initialize();
  return form;
}

IngredientForm *IngredientForm::editForm(Storable *object, QWidget *parent) {
  IngredientForm *form = new IngredientForm(parent);
  form->initialize();

  QIngredient *ingredient = qobject_cast<QIngredient *>(object);
  QVariantMap data;
  data["id"] = ingredient->getId();
  data["creatorId"] = ingredient->getCreatorId().toString();
  data["name"] = ingredient->getName();
  data["description"] = ingredient->getDescription();
  form->populateForm(data);

  return form;
}

bool IngredientForm::validateForm() {
  // Description can be empty
  if (m_nameEdit->text().isEmpty())
    return false;

  return true;
}

void IngredientForm::extractFormData() {
  m_data["name"] = m_nameEdit->text();
  m_data["description"] = m_descriptionEdit->toPlainText();
}

void IngredientForm::populateForm(const QVariantMap &data) {
  m_data = data;
  m_nameEdit->setText(m_data["name"].toString());
  m_descriptionEdit->setPlainText(m_data["description"].toString());
}

void IngredientForm::clearForm() {
  m_nameEdit->clear();
  m_descriptionEdit->clear();
}
