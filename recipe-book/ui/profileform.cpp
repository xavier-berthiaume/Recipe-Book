#include "profileform.h"
#include "ui_profileform.h"

ProfileForm::ProfileForm(Storable *object, QWidget *parent)
    : AbstractForm(PROFILEOBJECT, object, parent), ui(new Ui::ProfileForm) {}

ProfileForm::ProfileForm(QWidget *parent)
    : AbstractForm(PROFILEOBJECT, parent), ui(new Ui::ProfileForm) {}

ProfileForm::~ProfileForm() { delete ui; }

ProfileForm *ProfileForm::createForm(QWidget *parent) {
  ProfileForm *form = new ProfileForm(parent);
  form->initialize();
  return form;
}

ProfileForm *ProfileForm::editForm(Storable *object, QWidget *parent) {
  ProfileForm *form = new ProfileForm(object, parent);
  form->initialize();

  QProfile *profile = form->castObject<QProfile>(object);
  QVariantMap data;
  data["id"] = profile->getId();
  data["username"] = profile->getUsername();
  form->populateForm(data);

  return form;
}

void ProfileForm::initialize() {
  ui->setupUi(this);

  m_usernameEdit = findChild<QLineEdit *>("usernameEdit");

  connect(this, &QDialog::accepted, [this]() {
    if (!validateForm())
      return;

    extractFormData();
    if (isEditMode()) {
      qDebug() << "Submitted form to update profile" << m_data["id"].toString();
      emit updateRequested(objectType(), m_currentObject, m_data);
    } else {
      qDebug() << "Submitted form to create new profile";
      emit createRequested(objectType(), m_data);
    }
  });

  connect(this, &QDialog::rejected, [this]() { clearForm(); });
}

bool ProfileForm::validateForm() {

  if (m_usernameEdit->text().isEmpty())
    return false;

  return true;
}

void ProfileForm::extractFormData() {

  m_data["username"] = m_usernameEdit->text();
}

void ProfileForm::populateForm(const QVariantMap &data) {
  m_data = data;
  m_usernameEdit->setText(m_data["username"].toString());
}

void ProfileForm::clearForm() { m_usernameEdit->clear(); }
