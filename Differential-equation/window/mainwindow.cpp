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

    graphs.emplace_back(ui->SolutionPlot, true, "X axis", "Y axis", this);
    graphs.emplace_back(ui->ErrorPlot,   false, "X axis", "LTE", this);
    graphs.emplace_back(ui->MaxErrPlot,  false, "Step"  , "LTE", this);
    graphs[0].addGraphs({&exact, &euler, &impr_euler, &runge_kutta, &param});
    graphs[1].addGraphs({euler.getLte(), impr_euler.getLte(), runge_kutta.getLte()});
    graphs[2].addGraphs({&euler, &impr_euler, &runge_kutta});

    // connect Action buttons with a page change
    connect(ui->actSol,    &QAction::triggered, this, [=](){pageChange(0);});
    connect(ui->actErr,    &QAction::triggered, this, [=](){pageChange(1);});
    connect(ui->actMaxErr, &QAction::triggered, this, [=](){pageChange(2);});

    // connect press to change base point
    connect(ui->SolutionPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(basePointChange(QMouseEvent*)));
    // connect press to change base point
    ui->StepSlider->setRange(1,1500);
    connect(ui->StepSlider, SIGNAL(valueChanged(int)), this, SLOT(stepChange(int)));
    ui->StepSlider->setValue(300);

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

void MainWindow::stepChange(int value)
{
    ui->StepViewer->setText( QString::number(value/1000.));
    param.setStep(value/1000.);
}
