#include "recipeedit.h"
#include "ui_recipeedit.h"
#include <QDebug>
#include <QSqlError>

RecipeEdit::RecipeEdit(QWidget *parent, QSqlRelationalTableModel *recipeModel, QSqlRelationalTableModel *categoryModel) :
    QDialog(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);

    m_recipeModel = recipeModel;
    m_recipiesCategoriesModel = categoryModel;

    m_ingredientsModel = new QSqlRelationalTableModel(this);
    m_ingredientsModel->setTable("ingredients");
    m_ingredientsModel->select();

    ui->lstAllIngredients->setModel(m_ingredientsModel);
    ui->lstAllIngredients->setModelColumn(1);

    m_mapRecipeIngredientsModel = new QSqlRelationalTableModel(this);
    m_mapRecipeIngredientsModel->setTable("map_recipies_ingredients");
    m_mapRecipeIngredientsModel->setRelation(2, QSqlRelation("ingredients", "id", "name"));
    m_mapRecipeIngredientsModel->select();

    ui->lstAddedIngredients->setModel(m_mapRecipeIngredientsModel);
    ui->lstAddedIngredients->setModelColumn(2);

    ui->fldCategory->setModel(m_recipiesCategoriesModel);
    ui->fldCategory->setModelColumn(1);
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}

void RecipeEdit::init(int row)
{
    m_row = row;
    clear();
    if (row == -1) {
        m_record = m_recipeModel->record();
        ui->lstAddedIngredients->setEnabled(false);
        ui->lstAllIngredients->setEnabled(false);
        ui->btnAdd->setEnabled(false);
        ui->btnRemove->setEnabled(false);
        m_mapRecipeIngredientsModel->setFilter("recipie_id=0");
    } else {
        ui->lstAddedIngredients->setEnabled(true);
        ui->lstAllIngredients->setEnabled(true);
        ui->btnAdd->setEnabled(true);
        ui->btnRemove->setEnabled(true);
        m_recipeId = m_recipeModel->index(row, 0).data().toInt();
        m_record = m_recipeModel->record(row);
        QString name = m_recipeModel->index(row, 1).data().toString();
        QString description = m_recipeModel->index(row, 3).data().toString();
        QString category = m_recipeModel->index(row, 2).data().toString();
        ui->fldName->setText(name);
        ui->fldDescription->setPlainText(description);
        ui->fldCategory->setCurrentText(category);
        m_mapRecipeIngredientsModel->setFilter(QString("recipie_id=%1").arg(m_recipeId));
    }
}

void RecipeEdit::clear()
{
    ui->fldName->clear();
    ui->fldCategory->clear();
    ui->fldDescription->clear();
}

void RecipeEdit::getRecord()
{
    m_record.setValue(1, QVariant(ui->fldName->text()));
    m_record.setValue(2, ui->fldCategory->currentIndex() + 1);
    m_record.setValue(3, QVariant(ui->fldDescription->toPlainText()));
}

void RecipeEdit::on_buttonBox_accepted()
{
    getRecord();
    if (m_row == -1) {
        m_recipeModel->insertRecord(-1, m_record);
    } else {
        m_recipeModel->setRecord(m_row, m_record);
    }
    if (!m_recipeModel->submitAll()) {
        qDebug() << m_recipeModel->lastError().databaseText();
    }
    m_recipeModel->select();
}

void RecipeEdit::on_btnRemove_clicked()
{
    QModelIndexList selectedRows = ui->lstAddedIngredients->selectionModel()->selectedIndexes();
    if (selectedRows.size() == 0)
        return;
    auto index = selectedRows[0];
    if (!index.isValid())
        return;

    int row = index.row();
    m_mapRecipeIngredientsModel->removeRow(row);
    m_mapRecipeIngredientsModel->submitAll();
    m_mapRecipeIngredientsModel->select();
}

void RecipeEdit::on_btnAdd_clicked()
{
    QModelIndexList selectedRows = ui->lstAllIngredients->selectionModel()->selectedIndexes();
    if (selectedRows.size() == 0)
        return;
    auto index = selectedRows[0];
    if (!index.isValid())
        return;

    int row = index.row();
    int ingredientId = m_ingredientsModel->index(row, 0).data().toInt();
    auto record = m_mapRecipeIngredientsModel->record();
    record.setValue(1, m_recipeId);
    record.setValue(2, ingredientId);

    m_mapRecipeIngredientsModel->insertRecord(-1, record);
    m_mapRecipeIngredientsModel->submitAll();
    m_mapRecipeIngredientsModel->select();
}
