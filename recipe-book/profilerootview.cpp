#include "profilerootview.h"
#include "profilelistdelegate.h"
#include "ui_profilerootview.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

ProfileRootView::ProfileRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent), m_cache(cache), ui(new Ui::ProfileRootView),
      m_model(new ProfileListModel(this)), m_factory(new ProfileFactory(this)) {
  ui->setupUi(this);
  m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
  m_stackedWidget->setCurrentIndex(0);

  ProfileListDelegate *delegate = new ProfileListDelegate(this);
  QListView *list = m_stackedWidget->findChild<QListView *>("listView");
  m_model->populate(m_cache->getProfileCache());
  list->setModel(m_model);
  list->setItemDelegate(delegate);
  list->setMouseTracking(true);
  list->viewport()->setAttribute(Qt::WA_Hover);

  connect(
      delegate, &ProfileListDelegate::editClicked, this,
      [this](const QModelIndex &index) {
        QLabel *titleLabel = this->findChild<QLabel *>("formTitleLabel");
        QPushButton *confirmButton =
            this->findChild<QPushButton *>("confirmButton");
        QLineEdit *usernameEdit = this->findChild<QLineEdit *>("nameLineEdit");

        titleLabel->setText(tr("Update a Profile"));
        confirmButton->setText(tr("Update Profile"));
        usernameEdit->setText(
            m_model->data(index, ProfileListModel::UsernameRole).toString());

        m_editProfile = index;
        m_editMode = true;

        m_stackedWidget->setCurrentIndex(1);
      });

  connect(delegate, &ProfileListDelegate::deleteClicked, this,
          &ProfileRootView::deleteProfile);

  connect(delegate, &ProfileListDelegate::selectClicked, this,
          &ProfileRootView::selectProfile);

  connect(m_factory, &ProfileFactory::profileCreated, this,
          &ProfileRootView::profileCreated);
}

ProfileRootView::~ProfileRootView() { delete ui; }

void ProfileRootView::on_createButton_clicked() {
  m_editProfile = QModelIndex();
  m_editMode = false;

  QLabel *titleLabel = this->findChild<QLabel *>("formTitleLabel");
  QPushButton *confirmButton = this->findChild<QPushButton *>("confirmButton");
  QLineEdit *usernameEdit = this->findChild<QLineEdit *>("nameLineEdit");

  titleLabel->setText(tr("Create a Profile"));
  confirmButton->setText(tr("Create Profile"));
  usernameEdit->clear();

  m_stackedWidget->setCurrentIndex(1);
}

void ProfileRootView::on_cancelButton_clicked() {
  // Clear the form fields
  QLineEdit *nameField = findChild<QLineEdit *>("nameLineEdit");
  nameField->clear();
  m_stackedWidget->setCurrentIndex(0);
}

void ProfileRootView::on_nameLineEdit_textChanged(const QString &arg1) {
  QPushButton *confirmButton = findChild<QPushButton *>("confirmButton");
  confirmButton->setEnabled(!arg1.isEmpty());
}

void ProfileRootView::on_confirmButton_clicked() {
  QLineEdit *usernameEdit = findChild<QLineEdit *>("nameLineEdit");
  QString username = usernameEdit->text();

  if (m_editMode && m_editProfile.isValid()) {
    m_model->modifyProfile(m_editProfile.row(), QVariant(username),
                           ProfileListModel::UsernameRole);
  } else {
    m_factory->createProfile(username);
  }

  on_cancelButton_clicked();
}

void ProfileRootView::deleteProfile(const QModelIndex &index) {
  QDialog *confirmationDialog = new QDialog(this);
  confirmationDialog->setWindowTitle(tr("Confirm Deletion"));
  confirmationDialog->setModal(true);

  QVBoxLayout *layout = new QVBoxLayout(confirmationDialog);

  QLabel *message = new QLabel(
      tr("Are you sure you want to delete profile '%1'?")
          .arg(index.data(ProfileListModel::UsernameRole).toString()));
  message->setWordWrap(true);
  layout->addWidget(message);

  QDialogButtonBox *buttonBox = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, confirmationDialog);

  QPushButton *deleteButton = buttonBox->button(QDialogButtonBox::Ok);
  deleteButton->setText(tr("Delete"));
  deleteButton->setStyleSheet("color: red; font-weight: bold;");

  layout->addWidget(buttonBox);

  connect(buttonBox, &QDialogButtonBox::accepted, confirmationDialog,
          &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, confirmationDialog,
          &QDialog::reject);

  if (confirmationDialog->exec() == QDialog::Accepted) {
    // Order is important here
    m_cache->removeProfileFromCache(
        index.data(ProfileListModel::ProfileRole).value<QProfile *>());
    m_model->removeProfile(index.row());

    QMessageBox::information(this, tr("Profile Deleted"),
                             tr("The profile was successfully deleted."));
  }

  confirmationDialog->deleteLater();
}

void ProfileRootView::selectProfile(const QModelIndex &index) {
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
    QProfile *selectedProfile =
        index.data(ProfileListModel::ProfileRole).value<QProfile *>();
    emit selectedProfileChanged(selectedProfile);
    m_cache->setSelectedProfile(selectedProfile);
  }

  confirmationDialog->deleteLater();
}

void ProfileRootView::profileCreated(QProfile *newProfile) {
  newProfile->setParent(
      m_cache); // Set the cache as parent since it has a broader scope

  m_model->addProfile(newProfile);
  m_cache->addProfileToCache(newProfile);
}
