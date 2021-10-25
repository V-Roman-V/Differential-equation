#include "eulermethod.h"
EulerMethod::EulerMethod(ExactSolution* eq, Parameters* p)
    : ApproximationMethod("Euler",eq,p)
{}

bool EulerMethod::leftGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double step = p->step();
    double py = prev.value;

    double k1 = eq->getDifY(prev);
    QCPGraphData point{t, py - step*k1};
    data->add(point);
    prev = point;
    return true;
}

bool EulerMethod::rightGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double step = p->step();
    double py = prev.value;

    double k1 = eq->getDifY(prev);
    QCPGraphData point{t, py + step*k1};
    data->add(point);
    prev = point;
    return true;
}
