#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphics/plot.h>
#include <graphics/function.h>
#include <graphics/exactsolution.h>
#include <graphics/eulermethod.h>
#include <graphics/improvedeulermethod.h>
#include <graphics/rungekuttamethod.h>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void pageChange(int page_number);
    void graphUpdate();
    void basePointChange(QMouseEvent*);

    void stepChange(int value);

private:
    Parameters param;
    ExactSolution exact;
    EulerMethod euler;
    ImprovedEulerMethod impr_euler;
    RungeKuttaMethod runge_kutta;

    std::vector<Plot> graphs;
    Ui::MainWindow *ui;
    QTimer update_timer;
};
#endif // MAINWINDOW_H
