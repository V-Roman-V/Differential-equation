#include "plot.h"

Plot::Plot(QCustomPlot *plot, QObject *parent)
    : QObject(parent),
      plot(plot)
{
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectLegend);
    plot->xAxis->setLabel("x Axis");
    plot->yAxis->setLabel("y Axis");

    hidden_font.setPointSize(10);
    hidden_font.setItalic(true);
    hidden_font.setBold(true);

    legend_font.setPointSize(10);

    plot->legend->setFont(legend_font);
    plot->legend->setVisible(true);
    plot->legend->setSelectedFont(legend_font);
    plot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    // connect legendCLick to change visibility of graphics
    connect(plot, SIGNAL(legendClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(changeVisibility(QCPLegend*,QCPAbstractLegendItem*)));
}

Plot::Plot(const Plot &plot)
    : Plot(plot.plot,plot.parent())
{}


void Plot::addGraphs(const std::vector<Function*> &graphs)
{
    this->graphs.insert(this->graphs.end(), graphs.begin(), graphs.end());
    for(size_t i=0; i < graphs.size(); i++){
        plot->addGraph();
        plot->graph()->setName(graphs[i]->getName());
        plot->graph()->setPen(graphs[i]->getPen());
        plot->graph()->setScatterStyle(graphs[i]->getScatterStyle());
    }
}

void Plot::update()
{
    for(size_t i=0; i < graphs.size(); i++){
        if(plot->graph(i)->visible())
            plot->graph(i)->setData(graphs[i]->getData(plot->xAxis->range()));
    }
    plot->replot();
}

void Plot::changeVisibility(QCPLegend*, QCPAbstractLegendItem *item)
{
    // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    if (item){
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        if(plItem->plottable()->visible()){
            plItem->plottable()->setVisible(false);
            plItem->setFont(hidden_font);
            plItem->setSelectedFont(hidden_font);
        } else {
            plItem->plottable()->setVisible(true);
            plItem->setFont(legend_font);
            plItem->setSelectedFont(legend_font);
        }
        plot->replot();
    }
}
