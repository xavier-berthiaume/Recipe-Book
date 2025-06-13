#include "profilerootview.h"
#include "ui_profilerootview.h"

#include "profilelistdelegate.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

ProfileRootView::ProfileRootView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileRootView)
    , m_model(new ProfileListModel(this))
    , m_factory(new ProfileFactory(this))
{
    ui->setupUi(this);
    m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
    m_stackedWidget->setCurrentIndex(0);

    ProfileListDelegate *delegate = new ProfileListDelegate(this);
    QListView *list = m_stackedWidget->findChild<QListView *>("listView");
    list->setModel(m_model);
    list->setItemDelegate(delegate);
    list->setMouseTracking(true);
    list->viewport()->setAttribute(Qt::WA_Hover);

    connect(delegate, &ProfileListDelegate::editClicked,
            this, [this](const QModelIndex &index) {
        QLabel *titleLabel = this->findChild<QLabel *>("formTitleLabel");
        QPushButton *confirmButton = this->findChild<QPushButton *>("confirmButton");
        QLineEdit *usernameEdit = this->findChild<QLineEdit *>("nameLineEdit");

        titleLabel->setText(tr("Update a Profile"));
        confirmButton->setText(tr("Update Profile"));
        usernameEdit->setText(m_model->data(index, ProfileListModel::UsernameRole).toString());

        m_editProfile = index;
        m_editMode = true;

        m_stackedWidget->setCurrentIndex(1);
    });

    connect(delegate, &ProfileListDelegate::deleteClicked,
            this, [this](const QModelIndex &index) {
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
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
            confirmationDialog);

        QPushButton *deleteButton = buttonBox->button(QDialogButtonBox::Ok);
        deleteButton->setText(tr("Delete"));
        deleteButton->setStyleSheet("color: red; font-weight: bold;");

        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, confirmationDialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, confirmationDialog, &QDialog::reject);

        if (confirmationDialog->exec() == QDialog::Accepted) {
            this->m_model->removeProfile(index.row());

            QMessageBox::information(this,
                                     tr("Profile Deleted"),
                                     tr("The profile was successfully deleted."));
        }

        confirmationDialog->deleteLater();
    });

    connect(m_factory, &ProfileFactory::profileCreated, m_model, &ProfileListModel::profileCreated);
}

ProfileRootView::~ProfileRootView()
{
    delete ui;
}

void ProfileRootView::on_createButton_clicked()
{
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


void ProfileRootView::on_cancelButton_clicked()
{
    // Clear the form fields
    QLineEdit *nameField = findChild<QLineEdit *>("nameLineEdit");
    nameField->clear();
    m_stackedWidget->setCurrentIndex(0);
}


void ProfileRootView::on_nameLineEdit_textChanged(const QString &arg1)
{
    QPushButton *confirmButton = findChild<QPushButton *>("confirmButton");
    confirmButton->setEnabled(!arg1.isEmpty());
}


void ProfileRootView::on_confirmButton_clicked()
{
    QLineEdit *usernameEdit = findChild<QLineEdit *>("nameLineEdit");
    QString username = usernameEdit->text();

    if (m_editMode && m_editProfile.isValid()) {
        m_model->modifyProfile(m_editProfile.row(), QVariant(username), ProfileListModel::UsernameRole);
    } else {
        m_factory->createProfile(username);
    }

    on_cancelButton_clicked();
}

