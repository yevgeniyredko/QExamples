#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

    convertThread = new QThread(this);

    converter = new TextConverter();
    converter->moveToThread(convertThread);

    connect(this, SIGNAL(startConvertProcess(QString)), converter, SLOT(convertTextFiles(QString)));
    connect(converter, SIGNAL(maximumSet(int)), ui->progressBar, SLOT(setMaximum(int)));
    connect(converter, SIGNAL(currentFileChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(converter, SIGNAL(processFinished()), this, SLOT(on_processFinished()));

    convertThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    convertThread->quit();
    convertThread->wait();
    delete converter;
}

void MainWindow::on_getFolderButton_clicked()
{
    ui->folderEdit->setText(QFileDialog::getExistingDirectory(this));
}

void MainWindow::on_convertButton_clicked()
{
    if (!ui->folderEdit->text().isEmpty()) {
        emit startConvertProcess(ui->folderEdit->text());
        ui->convertButton->setEnabled(false);
    } else {
        QMessageBox::warning(this, "Warning", "Select folder!");
    }
}

void MainWindow::on_processFinished()
{
    ui->convertButton->setEnabled(true);
}
