#include "approximationmethod.h"

ApproximationMethod::ApproximationMethod(const QString& name, ExactSolution *eq, Parameters* p)
    : Function(name),
      eq(eq),
      p(p),
      lte(name),
      gte(name),
      maxlte(name),
      maxgte(name)
{}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::getData(const QCPRange &range) const
{
    return calculateData(range, p->step(), false);
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateData(const QCPRange& range, double step, bool useExact) const
{
    auto data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    const auto& base = p->base();

    // constrain the graph so as not to pass the point of discontinuity
    std::vector<double> edge(eq->pointDiscY());
    std::sort(edge.begin(),edge.end());
    double left = range.lower - step, right = range.upper + step;
    for(size_t i = 0; i < edge.size(); i++){
        if(left<edge[i] && edge[i]<base.key) left = edge[i];
        if(base.key<edge[i] && edge[i]<right) right = edge[i];
    }

    // graph construction
    QCPGraphData prev =  base;
    data->add(base);
    if(p->negative())
        for(double i = base.key - step; i > left + 1e-4; i-=step){ // go to left
            const auto& point = pointGenerator(i,prev,-step);
            data->add(point);
            prev = (useExact)?QCPGraphData{i,eq->getY(i)}:point;
        }
    prev = base;
    data->sort();
    if( p->positive())
        for(double i = base.key + step; i < right - 1e-4; i+=step){ // go to right
            const auto& point = pointGenerator(i,prev,step);
            data->add(point);
            prev = (useExact)?QCPGraphData{i,eq->getY(i)}:point;
        }
    return data;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateLTE(const QCPRange &range, double step, bool update)
{
    const auto& data = calculateData(range, step, true);
    auto LTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(const auto& point: *data){
        double lte = abs(point.value - eq->getY(point.key));
        LTEdata->add({point.key, lte});
    }
    if(update)lte.setData(LTEdata);
    return LTEdata;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateGTE(const QCPRange &range, double step, bool update)
{
    const auto& data = calculateData(range, step, false);
    auto GTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(const auto& point: *data){
        double gte = abs(point.value - eq->getY(point.key));
        GTEdata->add({point.key, gte});
    }
    if(update)gte.setData(GTEdata);
    return GTEdata;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateMaxLTE(const QCPRange &range, double min, double max, double shift, bool update)
{
    auto MaxLTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(double step = min; step<=max; step+=shift){
        const auto& ltedata = calculateLTE(range, step, false);
        double maxlte=0;
        for(const auto& point: *ltedata)
            if(point.value > maxlte)maxlte=point.value;
        MaxLTEdata->add({step,maxlte});
    }
    if(update)maxlte.setData(MaxLTEdata);
    return MaxLTEdata;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateMaxGTE(const QCPRange &range, double min, double max, double shift, bool update)
{
    auto MaxGTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(double step = min; step<=max; step+=shift){
        const auto& gtedata = calculateGTE(range, step, false);
        double maxgte=0;
        for(const auto& point: *gtedata)
            if(point.value > maxgte)maxgte=point.value;
        MaxGTEdata->add({step,maxgte});
    }
    if(update)maxgte.setData(MaxGTEdata);
    return MaxGTEdata;
}


void ApproximationMethod::updateErrors(const QCPRange& range, double min, double max, double shift)
{
    calculateLTE(range, p->step(), true);
    calculateGTE(range, p->step(), true);
    calculateMaxLTE(range, min, max, shift, true);
    calculateMaxGTE(range, min, max, shift, true);
}

Error *ApproximationMethod::getLte()
{
    lte.setPen(getPen());
    return &lte;
}
Error *ApproximationMethod::getGte()
{
    gte.setPen(getPen());
    return &gte;
}
Error *ApproximationMethod::getMaxlte()
{
    maxlte.setPen(getPen());
    return &maxlte;
}
Error *ApproximationMethod::getMaxgte()
{
    maxgte.setPen(getPen());
    return &maxgte;
}


bool ApproximationMethod::pointGenerator(double, double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
