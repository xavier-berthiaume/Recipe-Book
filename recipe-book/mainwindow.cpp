#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(DataCache *cache, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_cache(cache)
{
    ui->setupUi(this);

    profileButton = findChild<QPushButton *>("profileButton");
    ingredientButton = findChild<QPushButton *>("ingredientButton");
    recipeButton = findChild<QPushButton *>("recipeButton");

    m_centerStack = findChild<QStackedWidget *>("stackedWidget");

    m_profilePage = new ProfileRootView(m_cache, m_centerStack);
    m_centerStack->addWidget(m_profilePage);

    m_ingredientPage = new IngredientRootView(m_cache, m_centerStack);
    m_centerStack->addWidget(m_ingredientPage);

    m_recipePage = new RecipeRootView(m_cache, m_centerStack);
    m_centerStack->addWidget(m_recipePage);

    on_profileButton_pressed();
}

MainWindow::~MainWindow()
{
    delete ui;
}

DataCache *MainWindow::cache() const {
    return m_cache;
}

void MainWindow::on_profileButton_pressed()
{
    m_centerStack->setCurrentIndex(0);
    profileButton->setEnabled(false);

    ingredientButton->setEnabled(true);
    recipeButton->setEnabled(true);
}


void MainWindow::on_ingredientButton_pressed()
{
    m_centerStack->setCurrentIndex(1);
    ingredientButton->setEnabled(false);

    profileButton->setEnabled(true);
    recipeButton->setEnabled(true);
}


void MainWindow::on_recipeButton_pressed()
{
    m_centerStack->setCurrentIndex(2);
    recipeButton->setEnabled(false);

    profileButton->setEnabled(true);
    ingredientButton->setEnabled(true);
}
