#include "profileview.h"
#include "profileform.h"
#include "profilelistdelegate.h"
#include "ui_profileview.h"

ProfileView::ProfileView(QWidget *parent)
    : AbstractView(parent), ui(new Ui::ProfileView),
      m_profileModel(new ProfileListModel(this)) {
  ui->setupUi(this);

  m_listView = findChild<QListView *>("profileListView");
  m_listView->setModel(m_profileModel);
  m_listView->setItemDelegate(new ProfileListDelegate(this));

  m_editButton = findChild<QToolButton *>("editButton");
  m_deleteButton = findChild<QToolButton *>("deleteButton");
  m_loginButton = findChild<QPushButton *>("loginButton");
}

ProfileView::~ProfileView() { delete ui; }

void ProfileView::handleObjectCreated(ObjectTypes type, Storable *object) {
  qDebug() << "Adding profile to list model";

  switch (type) {
  case PROFILEOBJECT:
    m_profileModel->addModel(qobject_cast<QProfile *>(object));
    break;
  default:
    break;
  }
}

void ProfileView::handleObjectLoaded(ObjectTypes type, Storable *object) {
  handleObjectCreated(type, object); // Same logic applies
}

void ProfileView::on_createButton_clicked() {
  ProfileForm *form = ProfileForm::createForm(this);

  connect(form, &ProfileForm::createRequested, this,
          &ProfileView::createObjectRequested);

  form->exec();
}

void ProfileView::on_profileListView_clicked(const QModelIndex &index) {
  if (!index.isValid()) {
    m_editButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
    m_loginButton->setEnabled(false);
    return;
  }

  m_editButton->setEnabled(true);
  m_deleteButton->setEnabled(true);
  m_loginButton->setEnabled(true);
}

void ProfileView::on_deleteButton_clicked() {
  QProfile *profileToDelete =
      m_profileModel->getProfile(m_listView->currentIndex());

  if (profileToDelete == nullptr)
    return;

  qDebug() << "Requesting to delete profile with id"
           << profileToDelete->getId();
  m_profileModel->removeModel(m_listView->currentIndex().row());
  emit deleteObjectRequested(PROFILEOBJECT, profileToDelete);
}

void ProfileView::on_editButton_clicked() {
  QProfile *profileToUpdate =
      m_profileModel->getProfile(m_listView->currentIndex());

  if (profileToUpdate == nullptr)
    return;

  ProfileForm *form = ProfileForm::editForm(profileToUpdate, this);

  connect(form, &ProfileForm::updateRequested,
          [this, profileToUpdate](ObjectTypes type, Storable *object,
                                  const QVariantMap &data) {
            qDebug() << "Update form submitted with data" << data;
            profileToUpdate->setUsername(data["username"].toString());
            emit updateObjectRequested(type, object);
          });

  form->exec();
}
