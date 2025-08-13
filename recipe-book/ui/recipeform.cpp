#include "recipeform.h"
#include "ui_recipeform.h"
#include "stringeditdialog.h"

#include <QMessageBox>

RecipeForm::RecipeForm(Storable *object, QWidget *parent)
    : AbstractForm(RECIPEOBJECT, object, parent), ui(new Ui::RecipeForm) {}

RecipeForm::RecipeForm(QWidget *parent)
    : AbstractForm(RECIPEOBJECT, parent), ui(new Ui::RecipeForm) {}

RecipeForm::~RecipeForm() { delete ui; }

RecipeForm *RecipeForm::createForm(QWidget *parent) {
    RecipeForm *form = new RecipeForm(parent);
    form->initialize();

    return form;
}

RecipeForm *RecipeForm::editForm(Storable *object, QWidget *parent) {
    RecipeForm *form = new RecipeForm(object, parent);
    form->initialize();

    QRecipe *recipe = qobject_cast<QRecipe *>(object);
    QVariantMap data;
    data["name"] = recipe->getName();
    data["description"] = recipe->getDescription();
    data["notes"] = recipe->getNotes();
    data["instructions"] = recipe->getInstructions();
    data["equipment"] = recipe->getEquipment();
    // data["recipeIngredients"] = recipe->getIngredientIds();

    form->populateForm(data);
    return form;
}

bool RecipeForm::validateForm() {
    if (m_nameEdit->text().isEmpty())
        return false;

    // Make sure there's at least 1 instruction

    // Make sure there's at least 1 ingredient


    return true;
}

void RecipeForm::extractFormData() {}

void RecipeForm::populateForm(const QVariantMap &data) {}

void RecipeForm::clearForm() {}

void RecipeForm::initialize() {
    ui->setupUi(this);

    m_nameEdit = findChild<QLineEdit *>("nameEdit");
    m_descriptionEdit = findChild<QPlainTextEdit *>("descriptionEdit");
    m_notesEdit = findChild<QPlainTextEdit *>("notesEdit");

    m_instructionEdit = findChild<QLineEdit *>("instructionEdit");
    m_instructionWidget = findChild<QListWidget *>("instructionList");
    m_instructionCreate = findChild<QToolButton *>("addInstructionButton");
    m_instructionEditButton = findChild<QToolButton *>("editInstructionButton");
    m_instructionRemove = findChild<QToolButton *>("deleteInstructionButton");

    m_equipmentEdit = findChild<QLineEdit *>("equipmentEdit");
    m_equipmentWidget = findChild<QListWidget *>("equipmentList");
    m_equipmentCreate = findChild<QToolButton *>("addEquipmentButton");
    m_equipmentEditButton = findChild<QToolButton *>("editEquipmentButton");
    m_equipmentRemove = findChild<QToolButton *>("deleteEquipmentButton");

    m_recipeIngredientList = findChild<QListView *>("recipeIngredientList");

    connect(m_instructionCreate, &QToolButton::clicked, this, &RecipeForm::addInstructionToList);
    connect(m_instructionEdit, &QLineEdit::returnPressed, this, &RecipeForm::addInstructionToList);
    connect(m_equipmentCreate, &QToolButton::clicked, this, &RecipeForm::addEquipmentToList);
    connect(m_equipmentEdit, &QLineEdit::returnPressed, this, &RecipeForm::addEquipmentToList);

  connect(this, &QDialog::accepted, [this]() {
    if (!validateForm())
      return;

    extractFormData();
    if (isEditMode()) {
      qDebug() << "Submitted form to update recipe"
               << m_data["id"].toString();
      emit updateRequested(objectType(), m_currentObject, m_data);
    } else {
      qDebug() << "Submitted form to create new recipe";
      emit createRequested(objectType(), m_data);
    }
  });
}

void RecipeForm::addInstructionToList() {
    QString newItem = m_instructionEdit->text();

    if (newItem.isEmpty())
        return;

    m_instructionWidget->addItem(newItem);
    m_instructionEdit->clear();
}

void RecipeForm::addEquipmentToList() {
    QString newItem = m_equipmentEdit->text();

    if (newItem.isEmpty())
        return;

    m_equipmentWidget->addItem(newItem);
    m_equipmentEdit->clear();
}

void RecipeForm::on_instructionEdit_textChanged(const QString &arg1)
{
    m_instructionCreate->setEnabled(!arg1.isEmpty());
}


void RecipeForm::on_equipmentEdit_textChanged(const QString &arg1)
{
    m_equipmentCreate->setEnabled(!arg1.isEmpty());
}

void RecipeForm::on_instructionList_itemSelectionChanged()
{
    bool modEnabled = m_instructionWidget->currentItem();
    m_instructionEditButton->setEnabled(modEnabled);
    m_instructionRemove->setEnabled(modEnabled);
}


void RecipeForm::on_equipmentList_itemSelectionChanged()
{
    bool modEnabled = m_equipmentWidget->currentItem();
    m_equipmentEditButton->setEnabled(modEnabled);
    m_equipmentRemove->setEnabled(modEnabled);
}


void RecipeForm::on_deleteInstructionButton_clicked()
{
    m_instructionWidget->takeItem(m_instructionWidget->currentRow());
}


void RecipeForm::on_deleteEquipmentButton_clicked()
{
    m_equipmentWidget->takeItem(m_equipmentWidget->currentRow());
}


void RecipeForm::on_editInstructionButton_clicked()
{
    QListWidgetItem *currentItem = m_instructionWidget->currentItem();
    if (!currentItem) {
        QMessageBox::information(this, "No Selection", "Please select an item to edit");
        return;
    }

    StringEditDialog dialog(this);
    dialog.setText(currentItem->text());

    if (dialog.exec() == QDialog::Accepted) {
        QString newText = dialog.getText();
        if (!newText.isEmpty() && newText != currentItem->text()) {
            currentItem->setText(newText);
        }
    }
}


void RecipeForm::on_editEquipmentButton_clicked()
{
    QListWidgetItem *currentItem = m_equipmentWidget->currentItem();
    if (!currentItem) {
        QMessageBox::information(this, "No Selection", "Please select an item to edit");
        return;
    }

    StringEditDialog dialog(this);
    dialog.setText(currentItem->text());

    if (dialog.exec() == QDialog::Accepted) {
        QString newText = dialog.getText();
        if (!newText.isEmpty() && newText != currentItem->text()) {
            currentItem->setText(newText);
        }
    }
}

