#include "ingredient_root_view.h"

#include "ingredient_carousel_form.h"
#include "ingredient_display_box.h"

#include <QDialog>
#include <QRegularExpression>

IngredientRootView::IngredientRootView(
    const QList<QtIngredientWrapper *> &models, QWidget *parent)
    : m_ingredientFactory(nullptr), GenericRootView(models, parent) {

  connect(m_searchButton, &QPushButton::pressed, this,
          &IngredientRootView::searchButtonClicked);
  connect(m_createButton, &QPushButton::pressed, this,
          &IngredientRootView::createButtonClicked);

  displayModels();
}

void IngredientRootView::displayModels() {
  // Create a displaybox for each model, and add them to the grid view
  for (QtIngredientWrapper *model : m_models) {
    IngredientDisplayBox *displaybox = new IngredientDisplayBox(model, this);
    m_displayBoxArea->addWidget(displaybox);

    connect(displaybox, &IngredientDisplayBox::wrapperChanged, this,
            &IngredientRootView::updateView);
    connect(displaybox, &IngredientDisplayBox::destroyed, this,
            &IngredientRootView::updateView);
    connect(displaybox, &IngredientDisplayBox::clicked, this,
            &IngredientRootView::displayBoxClicked);
  }
}

void IngredientRootView::setFactory(IngredientFactory *factory) {
  m_ingredientFactory = factory;
}

void IngredientRootView::newIngredient(QtIngredientWrapper *ingredient) {
  qDebug() << "New ingredient created, added to the ingredient root view.";
  m_models.append(ingredient);
  updateView();
}

void IngredientRootView::displayBoxClicked(QtIngredientWrapper *ingredient) {
  emit ingredientClicked(ingredient);
}

void IngredientRootView::searchButtonClicked() {
  // Go through each display box, if the name of the display box doesn't regex
  // match what's the in search bar, hide it.
  QString searchText = m_searchBar->text().trimmed();
  QRegularExpression regex(searchText,
                           QRegularExpression::CaseInsensitiveOption);

  // Iterate through all display boxes
  for (int i = 0; i < m_displayBoxArea->count(); ++i) {
    QLayoutItem *item = m_displayBoxArea->itemAt(i);
    if (!item || !item->widget())
      continue;

    IngredientDisplayBox *displayBox =
        qobject_cast<IngredientDisplayBox *>(item->widget());
    if (displayBox) {
      bool match = regex.match(displayBox->wrapper()->getName()).hasMatch();
      displayBox->setVisible(match);
    }
  }
}

void IngredientRootView::createButtonClicked() {
  // Bring up a new window featuring the carousel form, destroy the window after
  // submission
  QDialog *dialog = new QDialog(this);
  dialog->setWindowTitle("Create New Ingredient");
  dialog->setMinimumSize(800, 600);
  dialog->setModal(true);
  dialog->setAttribute(Qt::WA_DeleteOnClose);

  IngredientCarouselForm *form = new IngredientCarouselForm(this);
  QVBoxLayout *layout = new QVBoxLayout(dialog);
  layout->addWidget(form);

  if (m_ingredientFactory != nullptr) {
    connect(form, &IngredientCarouselForm::formCompleted, m_ingredientFactory,
            &IngredientFactory::ingredientFormSubmitted);
  }

  dialog->show();
}

void IngredientRootView::updateView() {
  // Brute force just remove everything from
  // the grid view and add back in new display boxes
  QLayoutItem *item;
  while ((item = m_displayBoxArea->takeAt(0))) {
    if (QWidget *widget = item->widget()) {
      delete widget;
    }
    delete item;
  }

  displayModels();
}
