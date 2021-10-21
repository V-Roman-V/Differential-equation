#include "window/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , exact("Exact")
    , euler("Euler")
    , impr_euler("Improved Euler")
    , runga_kut("Runge-Kutta")
{
    ui->setupUi(this);

    graphs.emplace_back(ui->SolutionPlot);
    graphs.emplace_back(ui->ErrorPlot);
    graphs.emplace_back(ui->MaxErrPlot);
    graphs[0].addGraphs({&exact, &euler, &impr_euler, &runga_kut});
    graphs[1].addGraphs({&euler, &impr_euler, &runga_kut});
    graphs[2].addGraphs({&euler, &impr_euler, &runga_kut});

    graphs[0].update();
    graphs[1].update();
    graphs[2].update();

    // connect Action buttons with a page change
    connect(ui->actSol,    &QAction::triggered, this, [=](){pageChange(0);});
    connect(ui->actErr,    &QAction::triggered, this, [=](){pageChange(1);});
    connect(ui->actMaxErr, &QAction::triggered, this, [=](){pageChange(2);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pageChange(int page_number)
{
    graphs[0].update();
    graphs[1].update();
    graphs[2].update();
    ui->pages->setCurrentIndex(page_number);
}
