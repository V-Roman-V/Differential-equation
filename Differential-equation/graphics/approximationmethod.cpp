#include "approximationmethod.h"

ApproximationMethod::ApproximationMethod(const QString& name, ExactSolution *eq, Parameters* p)
    : Function(name),
      eq(eq),
      p(p),
      lte(new LTError(name)),
      maxlte( new MaxLTE(name))
{}

ApproximationMethod::~ApproximationMethod()
{
    delete lte;
    delete maxlte;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::getData(const QCPRange &range) const
{
    double ml;
    return calculateData(range, p->step(), ml, true);
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::calculateData(const QCPRange& range, double step, double& maxLTE, bool updateLTE)  const
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
        for(double i = base.key - step; i > left + 1e-4; i-=step) // go to left
            if(!leftGenerator(i,prev,step,data))break;
    prev = base;
    data->sort();
    if( p->positive())
        for(double i = base.key + step; i < right - 1e-4; i+=step) // go to right
            if(!rightGenerator(i,prev,step,data))break;

    //calculate LTE and maxLTE
    maxLTE = 0;
    auto LTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(const auto& point: *data){
        double lte = abs(point.value - eq->getY(point.key));
        if(lte > maxLTE) maxLTE = lte;
        LTEdata->add({point.key, lte});
    }
    if(updateLTE)lte->setData(LTEdata);

    return data;
}

void ApproximationMethod::updateMaxLTE(const QCPRange& range, double min, double max, double shift)
{
    auto MaxLTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(double step = min; step<=max; step+=shift){
        double maxlte;
        calculateData(range, step, maxlte, false);
        MaxLTEdata->add({step,maxlte});
    }
    maxlte->setData(MaxLTEdata);
}

LTError *ApproximationMethod::getLte() const
{
    lte->setPen(getPen());
    return lte;
}

MaxLTE *ApproximationMethod::getMaxlte() const
{
    maxlte->setPen(getPen());
    return maxlte;
}

bool ApproximationMethod::pointGenerator(double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
