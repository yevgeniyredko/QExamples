#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "textconverter.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void startConvertProcess(QString path);

private slots:
    void on_getFolderButton_clicked();
    void on_convertButton_clicked();
    void on_processFinished();

private:
    Ui::MainWindow *ui;
    TextConverter *converter;
    QThread *convertThread;
};

#endif // MAINWINDOW_H
