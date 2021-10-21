#include "plot.h"

Plot::Plot(QCustomPlot *plot)
    :plot(plot)
{
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->xAxis->setLabel("x Axis");
    plot->yAxis->setLabel("y Axis");

    legendFont.setPointSize(10);
    plot->legend->setFont(legendFont);
    plot->legend->setVisible(true);
}

void Plot::addGraphs(const std::vector<Function*> &graphs)
{
    this->graphs.insert(this->graphs.end(), graphs.begin(), graphs.end());
    for(int i=0; i<graphs.size(); i++){
        plot->addGraph();
        plot->graph()->setName(graphs[i]->getName());
        plot->graph()->setPen(graphs[i]->getPen());
    }
}

void Plot::update()
{
    for(int i=0; i < graphs.size(); i++)
        plot->graph(i)->setData(graphs[i]->getData());
    plot->replot();
}
