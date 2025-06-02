#include "ingredient_carousel_form.h"
#include "text_field.h"
#include "textarea_field.h"

IngredientCarouselForm::IngredientCarouselForm(QWidget *parent)
    : CarouselForm(parent) {
  addFormStep(new TextField("name", tr("Enter the Ingredient's Name")));

  TextAreaField *description = new TextAreaField(
      "description", tr("Enter a description for this Ingredient"));
  addFormStep(description);
  connect(description, &FormField::validChanged, this,
          &CarouselForm::currentStepDataChanged);
}
