#include "profileview.h"
#include "profileform.h"
#include "profilelistdelegate.h"
#include "profilelistmodel.h"
#include "ui_profileview.h"

#include <QDialogButtonBox>

ProfileView::ProfileView(QWidget *parent)
    : AbstractView(parent), ui(new Ui::ProfileView),
      m_profileModel(new ProfileListModel(this)), m_selectedProfile(nullptr) {
  ui->setupUi(this);

  m_listView = findChild<QListView *>("profileListView");
  m_listView->setModel(m_profileModel);
  m_listView->setItemDelegate(new ProfileListDelegate(this));

  m_loadMoreButton = findChild<QToolButton *>("loadMoreButton");

  m_editButton = findChild<QToolButton *>("editButton");
  m_deleteButton = findChild<QToolButton *>("deleteButton");
  m_loginButton = findChild<QPushButton *>("loginButton");

  m_loadedCountIndicator = findChild<QLabel *>("loadedCountIndicator");
  m_totalCountIndicator = findChild<QLabel *>("totalCountIndicator");
}

ProfileView::~ProfileView() { delete ui; }

void ProfileView::handleObjectsCounted(ObjectTypes type, int count) {
  m_totalCount = count;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void ProfileView::handleObjectCreated(ObjectTypes type, Storable *object) {
  qDebug() << "Adding profile to list model";

  switch (type) {
  case PROFILEOBJECT:
    m_profileModel->addModel(qobject_cast<QProfile *>(object));
    setLoadedCount();
    incrementTotalCount();
    break;

  default:
    break;
  }
}

void ProfileView::handleObjectLoaded(ObjectTypes type, Storable *object) {
  qDebug() << "Adding profile to list model";

  switch (type) {
  case PROFILEOBJECT:
    m_profileModel->addModel(qobject_cast<QProfile *>(object));
    setLoadedCount();

    if (m_totalCount == m_profileModel->rowCount()) {
      m_loadMoreButton->setEnabled(false);
    }
    break;

  default:
    break;
  }
}

void ProfileView::setLoadedCount() {
  m_loadedCountIndicator->setText(QString::number(m_profileModel->rowCount()));
}

void ProfileView::incrementTotalCount() {
  m_totalCount++;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void ProfileView::decrementTotalCount() {
  m_totalCount--;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
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

  if (m_selectedProfile == nullptr) {
    m_loginButton->setEnabled(true);
    return;
  }

  // Don't enable the login button if the currently selected profile is clicked
  // again
  if (m_selectedProfile->getId() ==
      m_profileModel->data(index, ProfileListModel::IdRole)) {
    m_loginButton->setEnabled(false);
    return;
  }

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

  if (m_selectedProfile != nullptr &&
      m_selectedProfile->getId() == profileToDelete->getId()) {
    m_selectedProfile = nullptr;
    findChild<QLabel *>("profileLabel")->setText(tr("No profile selected"));
  }

  setLoadedCount();
  decrementTotalCount();
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

void ProfileView::on_loginButton_clicked() {
  selectProfile(m_listView->currentIndex());
}

void ProfileView::on_loadMoreButton_clicked() {
  emit requestObjects(PROFILEOBJECT, m_profileModel->rowCount(), 10);
}

void ProfileView::selectProfile(const QModelIndex &index) {
  QDialog *confirmationDialog = new QDialog(this);
  confirmationDialog->setWindowTitle(tr("Confirm Deletion"));
  confirmationDialog->setModal(true);

  QVBoxLayout *layout = new QVBoxLayout(confirmationDialog);

  QLabel *message = new QLabel(
      tr("Are you sure you want to select profile '%1'?")
          .arg(index.data(ProfileListModel::UsernameRole).toString()));
  message->setWordWrap(true);
  layout->addWidget(message);

  QDialogButtonBox *buttonBox = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, confirmationDialog);

  QPushButton *confirmButton = buttonBox->button(QDialogButtonBox::Ok);
  confirmButton->setText(tr("Switch Profile"));

  layout->addWidget(buttonBox);
  connect(buttonBox, &QDialogButtonBox::accepted, confirmationDialog,
          &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, confirmationDialog,
          &QDialog::reject);

  if (confirmationDialog->exec() == QDialog::Accepted) {
    QProfile *clickedProfile = m_profileModel->getProfile(index);

    if (clickedProfile == nullptr)
      return;

    qDebug() << "Switching selected profiles";
    m_selectedProfile = clickedProfile;
    findChild<QLabel *>("profileLabel")
        ->setText(m_selectedProfile->getUsername());
    m_loginButton->setEnabled(false);
    emit selectedProfileChanged(clickedProfile);
  }
}
