#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "meshviewer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _meshViewer = new MeshViewer();
    QWidget *container = _meshViewer->container();
    setCentralWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
