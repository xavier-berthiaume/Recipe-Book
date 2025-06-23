#include "ingredientrootview.h"
#include "ui_ingredientrootview.h"
#include "ingredientlistdelegate.h"

#include <QDialog>
#include <QMessageBox>
#include <QDialogButtonBox>

IngredientRootView::IngredientRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IngredientRootView)
    , m_cache(cache)
    , m_model(new IngredientListModel(this))
    , m_factory(new IngredientFactory(this))
{
    ui->setupUi(this);
    m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
    m_stackedWidget->setCurrentIndex(0);

    IngredientListDelegate *delegate = new IngredientListDelegate(this);
    QListView *list = m_stackedWidget->findChild<QListView *>("listView");
    list->setModel(m_model);
    list->setItemDelegate(delegate);
    list->setMouseTracking(true);
    list->viewport()->setAttribute(Qt::WA_Hover);

    // Connect delegate edit and delete buttons
    connect(delegate, &IngredientListDelegate::editClicked, this, &IngredientRootView::editButtonClicked);
    connect(delegate, &IngredientListDelegate::deleteClicked, this, &IngredientRootView::deleteButtonClicked);

    // Connect factory creation function
    connect(m_factory, &IngredientFactory::ingredientCreated, this, &IngredientRootView::ingredientCreated);
}

IngredientRootView::~IngredientRootView()
{
    delete ui;
}

void IngredientRootView::on_createButton_clicked()
{
    m_editIngredient = QModelIndex();
    m_editMode = false;

    QLabel *titleLabel = this->findChild<QLabel *>("formTitleLabel");
    QPushButton *confirmButton = this->findChild<QPushButton *>("confirmButton");
    QLineEdit *nameEdit = this->findChild<QLineEdit *>("nameLineEdit");
    QPlainTextEdit *descriptionEdit = this->findChild<QPlainTextEdit *>("descriptionEdit");

    titleLabel->setText(tr("Create an Ingredient"));
    confirmButton->setText(tr("Create Ingredient"));
    nameEdit->clear();
    descriptionEdit->clear();

    m_stackedWidget->setCurrentIndex(1);
}


void IngredientRootView::on_cancelButton_clicked()
{
    QLineEdit *nameField = findChild<QLineEdit *>("nameLineEdit");
    QPlainTextEdit *descriptionField = findChild<QPlainTextEdit *>("descriptionEdit");

    nameField->clear();
    descriptionField->clear();

    m_stackedWidget->setCurrentIndex(0);
}


void IngredientRootView::on_nameLineEdit_textChanged(const QString &arg1)
{
    QPushButton *confirmButton = findChild<QPushButton *>("confirmButton");
    QPlainTextEdit *descriptionField = findChild<QPlainTextEdit *>("descriptionEdit");

    confirmButton->setEnabled(!arg1.isEmpty() && !descriptionField->toPlainText().isEmpty());
}


void IngredientRootView::on_descriptionEdit_textChanged()
{
    QPushButton *confirmButton = findChild<QPushButton *>("confirmButton");
    QLineEdit *nameField = findChild<QLineEdit *>("nameLineEdit");
    QPlainTextEdit *descriptionField = findChild<QPlainTextEdit *>("descriptionEdit");

    confirmButton->setEnabled(!nameField->text().isEmpty() && !descriptionField->toPlainText().isEmpty());
}


void IngredientRootView::on_confirmButton_clicked()
{
    QLineEdit *nameField = findChild<QLineEdit *>("nameLineEdit");
    QPlainTextEdit *descriptionField = findChild<QPlainTextEdit *>("descriptionEdit");

    QString name = nameField->text();
    QString description = descriptionField->toPlainText();

    if (m_editMode && m_editIngredient.isValid()) {
        m_model->modifyIngredient(m_editIngredient.row(), QVariant(name), IngredientListModel::NameRole);
        m_model->modifyIngredient(m_editIngredient.row(), QVariant(description), IngredientListModel::DescriptionRole);
    } else {
        m_factory->createIngredient(m_cache->getSelectedProfile(), name, description);
    }

    on_cancelButton_clicked();
}

void IngredientRootView::editButtonClicked(const QModelIndex &index) {
    QLabel *titleLabel = this->findChild<QLabel *>("formTitleLabel");
    QPushButton *confirmButton = this->findChild<QPushButton *>("confirmButton");

    QLineEdit *nameEdit = this->findChild<QLineEdit *>("nameLineEdit");
    QPlainTextEdit *descriptionEdit = this->findChild<QPlainTextEdit *>("descriptionEdit");

    titleLabel->setText(tr("Update an Ingredient"));
    confirmButton->setText(tr("Update Ingredient"));

    nameEdit->setText(index.data(IngredientListModel::NameRole).toString());
    descriptionEdit->setPlainText(index.data(IngredientListModel::DescriptionRole).toString());

    m_editIngredient = index;
    m_editMode = true;

    m_stackedWidget->setCurrentIndex(1);
}

void IngredientRootView::deleteButtonClicked(const QModelIndex &index) {
        QDialog *confirmationDialog = new QDialog(this);
        confirmationDialog->setWindowTitle(tr("Confirm Deletion"));
        confirmationDialog->setModal(true);

        QVBoxLayout *layout = new QVBoxLayout(confirmationDialog);

        QLabel *message = new QLabel(
            tr("Are you sure you want to delete the ingredient '%1'?")
                .arg(index.data(IngredientListModel::NameRole).toString()));
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
            this->m_model->removeIngredient(index.row());

            QMessageBox::information(this,
                                     tr("Ingredient Deleted"),
                                     tr("The Ingredient was successfully deleted."));
        }

        confirmationDialog->deleteLater();
}

void IngredientRootView::ingredientCreated(QIngredient *newIngredient) {
    m_cache->addIngredientToCache(newIngredient);
    m_model->addIngredient(newIngredient);
}
