#ifndef PLOT_H
#define PLOT_H

#include <QObject>

#include <QFont>
#include <vector>
#include "QCustomPlot/qcustomplot.h"
#include "function.h"

class Plot : public QObject
{
    Q_OBJECT

public:
    Plot(QCustomPlot *plot, bool interact, QString xAxis, QString yAxis, QObject *parent = nullptr);
    Plot(const Plot& plot);

    void addGraphs(const std::vector<Function *> &graphs);

    void update();

private slots:
    void changeVisibility(QCPLegend* legend, QCPAbstractLegendItem* item);

private:
    std::vector<Function*> graphs;
    bool interact;
    QString xName, yName;
    QFont legend_font, hidden_font;
    QCustomPlot* plot;
};

#endif // PLOT_H
