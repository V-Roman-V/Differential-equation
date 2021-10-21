#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphics/plot.h>
#include <graphics/function.h>
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

private:
    Function exact;
    Function euler;
    Function impr_euler;
    Function runga_kut;

    std::vector<Plot> graphs;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
