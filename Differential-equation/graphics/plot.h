#ifndef GRAPH_H
#define GRAPH_H

#include <QFont>
#include <vector>
#include "QCustomPlot/qcustomplot.h"
#include "function.h"

class Plot
{
public:
    Plot(QCustomPlot* plot);

    void addGraphs(const std::vector<Function *> &graphs);

    void update();
private:
    std::vector<Function*> graphs;
    QFont legendFont;
    QCustomPlot* plot;
};

#endif // GRAPH_H
