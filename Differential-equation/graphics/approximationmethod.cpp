#include "approximationmethod.h"

ApproximationMethod::ApproximationMethod(const QString& name, ExactSolution *eq, Parameters* p)
    : Function(name),
      eq(eq),
      p(p),
      lte(new LTError(name))
{}

ApproximationMethod::~ApproximationMethod()
{
    delete lte;
}

QSharedPointer<QCPGraphDataContainer> ApproximationMethod::getData(const QCPRange &range) const
{
    auto data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    const auto& base = p->base();
    double step = p->step();

    // constrain the graph so as not to pass the point of discontinuity
    std::vector<double> edge(eq->pointDiscY());
    std::sort(edge.begin(),edge.end());
    double left = range.lower - step, right = range.upper + step;
    for(size_t i = 0; i < edge.size(); i++){
        if(left<edge[i] && edge[i]<base.key) left = edge[i];
        if(base.key<edge[i] && edge[i]<right) right = edge[i];
    }

    QCPGraphData prev =  base;
    data->add(base);
    for(double i = base.key - step; i >= left; i-=step) // go to left
        if(!leftGenerator(i,prev,data))break;

    prev = base;
    data->sort();
    for(double i = base.key + step; i <= right; i+=step) // go to right
        if(!rightGenerator(i,prev,data))break;

    //culculate LTE
    auto LTEdata = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    for(const auto& point: *data)
        LTEdata->add({point.key, abs(point.value - eq->getY(point.key))});
    lte->setData(LTEdata);

    return data;
}

bool ApproximationMethod::pointGenerator(double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}

LTError *ApproximationMethod::getLte() const
{
    return lte;
}
