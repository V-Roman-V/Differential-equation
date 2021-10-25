#include "window/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , euler(&exact, &param)
    , impr_euler(&exact, &param)
    , runge_kutta(&exact, &param)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphs.emplace_back(ui->SolutionPlot, this);
    graphs.emplace_back(ui->ErrorPlot, this);
    graphs.emplace_back(ui->MaxErrPlot, this);
    graphs[0].addGraphs({&exact, &euler, &impr_euler, &runge_kutta, &param});
    graphs[1].addGraphs({&euler, &impr_euler, &runge_kutta});
    graphs[2].addGraphs({&euler, &impr_euler, &runge_kutta});

    // connect Action buttons with a page change
    connect(ui->actSol,    &QAction::triggered, this, [=](){pageChange(0);});
    connect(ui->actErr,    &QAction::triggered, this, [=](){pageChange(1);});
    connect(ui->actMaxErr, &QAction::triggered, this, [=](){pageChange(2);});

    // connect press to change base point
    connect(ui->SolutionPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(basePointChange(QMouseEvent*)));

    // connect Timer to update graphics
    connect(&update_timer, SIGNAL(timeout()), this, SLOT(graphUpdate()));
    update_timer.start(25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pageChange(int page_number)
{
    graphUpdate();
    ui->pages->setCurrentIndex(page_number);
}

void MainWindow::graphUpdate()
{
    for(auto& graph: graphs)
        graph.update();
}

void MainWindow::basePointChange(QMouseEvent *event)
{
    if(event->button() != Qt::MouseButton::LeftButton)return;
    QPointF pos(event->x(),event->y());
    auto axis = ui->SolutionPlot->axisRectAt(pos);
    int left = axis->left(), width = axis->width();
    double t = (pos.x() - left)/width;
    double x = ui->SolutionPlot->xAxis->range().lower + ui->SolutionPlot->xAxis->range().size()*t;
    param.setBasePoint({x, exact.getY(x)});
}
