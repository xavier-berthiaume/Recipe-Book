#include "recipe_carousel_form.h"
#include "text_field.h"
#include "textarea_field.h"
#include "textlist_field.h"

// Still missing 2 fields, prep time and ingredients
RecipeCarouselForm::RecipeCarouselForm(QWidget *parent) : CarouselForm(parent) {
  addFormStep(new TextField("name", tr("Enter the Recipe's Name")));
  addFormStep(new TextAreaField("description",
                                tr("Enter a description of your Recipe")));

  TextListField *instructions = new TextListField(
      "instructions", tr("What are the steps to making this Recipe?"), false);
  addFormStep(instructions);
  connect(instructions, &TextListField::fieldChanged, this,
          &CarouselForm::currentStepDataChanged);

  addFormStep(new TextAreaField("notes",
                                tr("Are there any special notes that should be "
                                   "kept in mind when making this Recipe?")));

  TextListField *equipment = new TextListField(
      "equipment", tr("What equipment is required to make this recipe?"));
  addFormStep(equipment);
  connect(equipment, &TextListField::fieldChanged, this,
          &CarouselForm::currentStepDataChanged);
}
