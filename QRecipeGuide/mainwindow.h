#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "recipeedit/recipeedit.h"
#include "ingredientedit/ingredientedit.h"

#include <QMainWindow>
#include <QSqlRelationalTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAddRecipe_triggered();
    void on_actionViewIngredients_triggered();
    void on_lstCategories_clicked(const QModelIndex &index);
    void on_lstRecipies_doubleClicked(const QModelIndex &index);
    void on_actionViewHelp_triggered();

private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *m_recipiesCategoriesModel;
    QSqlRelationalTableModel *m_recipeModel;
    IngredientEdit *m_ingredientEditForm;
    RecipeEdit *m_recipeEditForm;
};

#endif // MAINWINDOW_H
