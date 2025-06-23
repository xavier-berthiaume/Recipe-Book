#include "ingredientselectordialog.h"
#include "ui_ingredientselectordialog.h"

#include "qrecipeingredient.h"

IngredientSelectorDialog::IngredientSelectorDialog(DataCache *cache, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IngredientSelectorDialog)
    , m_cache(cache)
{
    ui->setupUi(this);

    ingredientModel = new IngredientListModel(this);
    delegate = new IngredientSelectionDelegate(this);

    if (m_cache) {
        ingredientModel->populate(m_cache->getIngredientCache());
    }

    m_ingredientButton = findChild<QPushButton *>("ingredientButton");
    m_recipeButton = findChild<QPushButton *>("recipeButton");
    m_okButton = findChild<QDialogButtonBox *>("buttonBox")->button(QDialogButtonBox::Ok);
    m_quantitySpinbox = findChild<QDoubleSpinBox *>("quantitySpinbox");
    m_unitCombobox = findChild<QComboBox *>("unitCombobox");
    m_listView = findChild<QListView *>("listView");

    on_ingredientButton_pressed();

    m_listView->setItemDelegate(delegate);

    m_quantitySpinbox->setMinimum(0);
    m_quantitySpinbox->setMaximum(99999);

    QMap<QString, QRecipeIngredient::Units> comboboxOptions = QRecipeIngredient::unitOptions();
    int defaultIndex = 0;
    for (auto unitEntry = comboboxOptions.begin(); unitEntry != comboboxOptions.end(); unitEntry++) {
        m_unitCombobox->addItem(unitEntry.key(), unitEntry.value());
        if (unitEntry.value() == QRecipeIngredient::Units::Grams) defaultIndex = m_unitCombobox->count()-1;
    }

    m_unitCombobox->setCurrentIndex(defaultIndex);

    m_okButton->setEnabled(false);
    if (!m_okButton->isEnabled()) {
        m_okButton->setToolTip(tr("Please complete all required fields"));
    }
}

IngredientSelectorDialog::~IngredientSelectorDialog()
{
    delete ui;
}

bool IngredientSelectorDialog::validateFields() {
    if (m_quantitySpinbox->value() == 0 || m_quantitySpinbox->value() > 99999) return false;
    if (m_unitCombobox->currentIndex() < 0 || m_unitCombobox->currentIndex() >= m_unitCombobox->count()) return false;
    if (!m_listView->currentIndex().isValid()) return false;

    return true;
}

void IngredientSelectorDialog::on_ingredientButton_pressed()
{
    m_ingredientButton->setDisabled(true);
    m_recipeButton->setDisabled(false);
    // Change the model that's represented in the listview
    m_listView->setModel(ingredientModel);

}


void IngredientSelectorDialog::on_recipeButton_pressed()
{
    m_ingredientButton->setDisabled(false);
    m_recipeButton->setDisabled(true);
    // Change the model that's represented in the listview

}

void IngredientSelectorDialog::on_quantitySpinbox_valueChanged(double arg1)
{
    if (validateFields()) {
        m_okButton->setEnabled(true);
    } else {
        m_okButton->setEnabled(false);
    }
}


void IngredientSelectorDialog::on_unitCombobox_currentIndexChanged(int index)
{
    if (validateFields()) {
        m_okButton->setEnabled(true);
    } else {
        m_okButton->setEnabled(false);
    }
}


void IngredientSelectorDialog::on_listView_indexesMoved(const QModelIndexList &indexes)
{
    if (validateFields()) {
        m_okButton->setEnabled(true);
    } else {
        m_okButton->setEnabled(false);
    }

}

