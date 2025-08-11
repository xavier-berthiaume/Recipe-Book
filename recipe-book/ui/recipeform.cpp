#include "recipeform.h"
#include "ui_recipeform.h"

RecipeForm::RecipeForm(Storable *object, QWidget *parent)
    : AbstractForm(RECIPEOBJECT, object, parent), ui(new Ui::RecipeForm) {}

RecipeForm::RecipeForm(QWidget *parent)
    : AbstractForm(RECIPEOBJECT, parent), ui(new Ui::RecipeForm) {}

RecipeForm::~RecipeForm() { delete ui; }

RecipeForm *RecipeForm::createForm(QWidget *parent) {}

RecipeForm *RecipeForm::editForm(Storable *object, QWidget *parent) {}

bool RecipeForm::validateForm() {}

void RecipeForm::extractFormData() {}

void RecipeForm::populateForm(const QVariantMap &data) {}

void RecipeForm::clearForm() {}

void RecipeForm::initialize() {}
