#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "copier.h"
#include <QThread>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

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
    void copyProcessStarted(QString from, QString to);

private slots:
    void on_pathFromButton_clicked();
    void on_pathToButton_clicked();
    void on_copyButton_clicked();
    void on_processFinished();
    int on_fileExists(QString fileName);

private:
    Ui::MainWindow *ui;
    QString getDirectory();
    Copier* copier;
    QThread* copyThread;
};

#endif // MAINWINDOW_H
