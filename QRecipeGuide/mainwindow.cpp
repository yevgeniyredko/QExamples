#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
        qDebug() << db.lastError();
    }

    QSqlQuery q(db);
    q.exec("PRAGMA foreign_keys ON;");

    m_recipiesCategoriesModel = new QSqlRelationalTableModel(this);
    m_recipiesCategoriesModel->setTable("categories");
    m_recipiesCategoriesModel->select();
    ui->lstCategories->setModel(m_recipiesCategoriesModel);
    ui->lstCategories->setModelColumn(1);

    m_recipeModel = new QSqlRelationalTableModel(this);
    m_recipeModel->setTable("recipies");
    m_recipeModel->setFilter("category=1");
    m_recipeModel->select();
    m_recipeModel->setRelation(2, QSqlRelation("categories", "id", "name"));
    ui->lstRecipies->setModel(m_recipeModel);
    ui->lstRecipies->setModelColumn(1);

    m_ingredientEditForm = new IngredientEdit(this);
    m_ingredientEditForm->setModal(true);
    m_recipeEditForm = new RecipeEdit(this, m_recipeModel, m_recipiesCategoriesModel);
    m_recipeEditForm->setModal(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddRecipe_triggered()
{
    m_recipeEditForm->init();
    m_recipeEditForm->show();
}

void MainWindow::on_actionViewIngredients_triggered()
{
    m_ingredientEditForm->show();
}

void MainWindow::on_lstCategories_clicked(const QModelIndex &index)
{
    m_recipeModel->setFilter(QString("category=%1").arg(index.row() + 1));
    m_recipeModel->select();
}

void MainWindow::on_lstRecipies_doubleClicked(const QModelIndex &index)
{
    m_recipeEditForm->init(index.row());
    m_recipeEditForm->show();
}

void MainWindow::on_actionViewHelp_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("help/help.html"));
}
