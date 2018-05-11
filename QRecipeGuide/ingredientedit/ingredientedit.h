#ifndef INGREDIENTEDIT_H
#define INGREDIENTEDIT_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class IngredientEdit;
}

class IngredientEdit : public QDialog
{
    Q_OBJECT

public:
    explicit IngredientEdit(QWidget *parent = 0);
    ~IngredientEdit();

private:
    Ui::IngredientEdit *ui;
    QSqlRelationalTableModel *m_ingredientsModel;
};

#endif // INGREDIENTEDIT_H
