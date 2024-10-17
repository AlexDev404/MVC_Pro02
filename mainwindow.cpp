#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    QString mPath="C:/Blaze";

    // .. Glue
    ui->treeView->setModel(model);

    // .. Set the root path
    QModelIndex rootIndex = model->index(mPath);
    ui->treeView->setRootIndex(rootIndex);

    // .. Make it editable
    model->setReadOnly(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createDirectory_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();

    if(!index.isValid()) return;
    QString name = QInputDialog::getText(this, "Name", "Enter Folder Name");

    if(name.isEmpty()) return;
    model->mkdir(index, name);
}


void MainWindow::on_deleteDirectory_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();

    if(model->fileInfo(index).isDir()){
        // Directory
        model->rmdir(index);
        return;
    }
    // File
    model->remove(index);
}
