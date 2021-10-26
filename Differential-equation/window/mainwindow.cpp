#include "window/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , euler(&exact, &param)
    , impr_euler(&exact, &param)
    , runge_kutta(&exact, &param)
    , ui(new Ui::MainWindow)
    , PositiveDirect("positive direction", ui->statBar)
    , NegativeDirect("negative direction", ui->statBar)
{
    ui->setupUi(this);

    graphs.emplace_back(ui->SolutionPlot, true, "X axis", "Y axis", this);
    graphs.emplace_back(ui->ErrorPlot,   false, "X axis", "LTE", this);
    graphs.emplace_back(ui->MaxErrPlot,  false, "Step"  , "LTE", this);
    graphs[0].addGraphs({&exact, &euler, &impr_euler, &runge_kutta, &param});
    graphs[1].addGraphs({euler.getLte(), impr_euler.getLte(), runge_kutta.getLte()});
    graphs[2].addGraphs({euler.getMaxlte(), impr_euler.getMaxlte(), runge_kutta.getMaxlte()});

    // connect Action buttons with a page change
    connect(ui->actSol,    &QAction::triggered, this, [=](){pageChange(0);});
    connect(ui->actErr,    &QAction::triggered, this, [=](){pageChange(1);});
    connect(ui->actMaxErr, &QAction::triggered, this, [=](){pageChange(2);});

    // connect press with change base point
    connect(ui->SolutionPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(basePointChange(QMouseEvent*)));
    // connect slider with steps
    ui->StepSlider->setRange(1,1500);
    connect(ui->StepSlider, SIGNAL(valueChanged(int)), this, SLOT(stepChange(int)));
    ui->StepSlider->setValue(100);

    // connect Timer to update graphics
    connect(&update_timer, SIGNAL(timeout()), this, SLOT(graphUpdate()));
    update_timer.start(25);

    // connect checkBox
    connect(&PositiveDirect, SIGNAL(stateChanged(int)),this, SLOT(dirPosChange(int)));
    connect(&NegativeDirect, SIGNAL(stateChanged(int)),this, SLOT(dirNegChange(int)));
    PositiveDirect.setChecked(true);
    NegativeDirect.setChecked(true);
    ui->statBar->addWidget(&PositiveDirect);
    ui->statBar->addWidget(&NegativeDirect);

    ui->SolutionPlot->xAxis->setRange(1,9);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pageChange(int page_number)
{
    if(ui->pages->currentIndex() != page_number)
        graphUpdate();
    ui->pages->setCurrentIndex(page_number);
}

void MainWindow::graphUpdate()
{
    if(ui->pages->currentIndex() == 2)
        graphUpdateMaxLTE();

    for(auto& graph: graphs)
        graph.update();
}

void MainWindow::graphUpdateMaxLTE()
{
    const auto& range = ui->SolutionPlot->xAxis->range();
    double minS = ui->StepSlider->minimum()/1000.;
    double maxS = ui->StepSlider->maximum()/1000.;
    double step = (maxS-minS)/100.;
    euler.updateMaxLTE(range, minS, maxS, step);
    impr_euler.updateMaxLTE(range, minS, maxS, step);
    runge_kutta.updateMaxLTE(range, minS, maxS, step);
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
    ui->StepViewer->setText(QString::number(value/1000.));
    param.setStep(value/1000.);
}

void MainWindow::dirPosChange(int pos)
{
    graphUpdate();
    param.setPositive(pos);
}

void MainWindow::dirNegChange(int neg)
{
    graphUpdate();
    param.setNegative(neg);
}
