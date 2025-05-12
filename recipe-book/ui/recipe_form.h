#ifndef RECIPE_FORM_H
#define RECIPE_FORM_H

#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QWidget>

#include "../models/qt_recipe_wrapper.h"

class RecipeForm : public QWidget {
  Q_OBJECT

public:
  explicit RecipeForm(QWidget *parent = nullptr);
  ~RecipeForm();

  QtRecipeWrapper *getRecipeWrapper() const;

signals:
  void recipeCreated(QtRecipeWrapper *recipe);

private slots:
  void handleSubmit();
  void addInstruction();
  void removeInstruction();
  void addEquipment();
  void removeEquipment();

private:
  void setupUi();
  void connectSignals();

  // Form widgets
  QLineEdit *m_nameEdit;
  QTextEdit *m_descriptionEdit;
  QTextEdit *m_notesEdit;
  QSpinBox *m_prepTimeSpin;
  QCheckBox *m_isSharedCheck;
  QSpinBox *m_likeCountSpin;

  // Lists for instructions and equipment
  QListWidget *m_instructionsList;
  QLineEdit *m_newInstructionEdit;
  QListWidget *m_equipmentList;
  QLineEdit *m_newEquipmentEdit;

  // Buttons
  QPushButton *m_submitButton;

  // Layout
  QFormLayout *m_mainLayout;

  QtRecipeWrapper *m_recipeWrapper;
};

#endif
