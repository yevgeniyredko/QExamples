#ifndef RECIPEEDIT_H
#define RECIPEEDIT_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

namespace Ui {
class RecipeEdit;
}

class RecipeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeEdit(QWidget *parent = 0, QSqlRelationalTableModel *recipeModel = 0, QSqlRelationalTableModel *categoryModel = 0);
    ~RecipeEdit();
    void init(int row = -1);

private slots:
    void on_buttonBox_accepted();
    void on_btnRemove_clicked();
    void on_btnAdd_clicked();

private:
    Ui::RecipeEdit *ui;
    int m_row;
    int m_recipeId;
    QSqlRecord m_record;

    QSqlRelationalTableModel *m_mapRecipeIngredientsModel;
    QSqlRelationalTableModel *m_ingredientsModel;
    QSqlRelationalTableModel *m_recipiesCategoriesModel;
    QSqlRelationalTableModel *m_recipeModel;

    void clear();
    void getRecord();
};

#endif // RECIPEEDIT_H
