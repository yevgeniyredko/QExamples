#include "ingredientedit.h"
#include "ui_ingredientedit.h"

IngredientEdit::IngredientEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IngredientEdit)
{
    ui->setupUi(this);

    m_ingredientsModel = new QSqlRelationalTableModel(this);
    m_ingredientsModel->setTable("ingredients");
    m_ingredientsModel->select();
    ui->lstIngredients->setModel(m_ingredientsModel);
    ui->lstIngredients->setModelColumn(1);
}

IngredientEdit::~IngredientEdit()
{
    delete ui;
}
