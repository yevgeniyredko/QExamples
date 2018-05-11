#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    copyThread = new QThread(this);
    connect(this, SIGNAL(destroyed()), copyThread, SLOT(quit()));

    copier = new Copier();
    copier->moveToThread(copyThread);

    connect(this, SIGNAL(copyProcessStarted(QString,QString)), copier, SLOT(copyDirectory(QString,QString)));
    connect(copier, SIGNAL(maximumSet(int)), ui->progressBar, SLOT(setMaximum(int)));
    connect(copier, SIGNAL(currentFileChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(copier, SIGNAL(processFinished()), this, SLOT(on_processFinished()));
    connect(copier, SIGNAL(fileExists(QString)), this, SLOT(on_fileExists(QString)), Qt::BlockingQueuedConnection);

    copyThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    copyThread->quit();
    copyThread->wait();
    delete copier;
}

void MainWindow::on_pathFromButton_clicked()
{
    ui->pathFromText->setText(getDirectory());
}

void MainWindow::on_pathToButton_clicked()
{
    ui->pathToText->setText(getDirectory());
}

void MainWindow::on_copyButton_clicked()
{
    if (ui->pathFromText->text() != QString("") && ui->pathToText->text() != QString("")) {
        ui->copyButton->setEnabled(false);
        emit copyProcessStarted(ui->pathFromText->text(), ui->pathToText->text());
    }
    else QMessageBox::warning(this, QString("Warning"), QString("Select folders!"));
}

void MainWindow::on_processFinished()
{
    ui->copyButton->setEnabled(true);
}

int MainWindow::on_fileExists(QString fileName)
{
    auto result = QMessageBox::warning(this, "Warning",
                                       QString("File %1 exisis. Do you want to replace?").arg(fileName),
                                       QMessageBox::Yes, QMessageBox::No);
    return result == QMessageBox::Yes;
}


QString MainWindow::getDirectory()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    if(dialog.exec()) {
        return dialog.directory().absolutePath();
    } else return QString("");
}
