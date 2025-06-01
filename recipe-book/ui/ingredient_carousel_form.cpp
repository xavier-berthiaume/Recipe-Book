#include "ingredient_carousel_form.h"
#include "text_field.h"
#include "textarea_field.h"
#include "textlist_field.h"

IngredientCarouselForm::IngredientCarouselForm(QWidget *parent)
    : CarouselForm(parent) {
  addFormStep(new TextField("name", tr("Enter the Ingredient's Name")));
  addFormStep(new TextAreaField("description",
                                tr("Enter a description for this Ingredient")));
}
