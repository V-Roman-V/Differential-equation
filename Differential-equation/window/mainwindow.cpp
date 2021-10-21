#include "window/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect Action buttons with a page change
    connect(ui->actSol,    &QAction::triggered, this, [=](){changePage(0);});
    connect(ui->actErr,    &QAction::triggered, this, [=](){changePage(1);});
    connect(ui->actMaxErr, &QAction::triggered, this, [=](){changePage(2);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(int pageNumber)
{
    qDebug()<<pageNumber;
    ui->pages->setCurrentIndex(pageNumber);
}

