#include "eulermethod.h"
EulerMethod::EulerMethod(ExactSolution* eq, Parameters* p)
    : ApproximationMethod("Euler",eq,p)
{
    pen.setColor(QColor(21,225,235));
}

bool EulerMethod::leftGenerator(double t, QCPGraphData& prev, double step, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double py = prev.value;

    double k1 = eq->getDifY(prev);
    QCPGraphData point{t, py - step*k1};
    data->add(point);
    prev = point;
    return true;
}

bool EulerMethod::rightGenerator(double t, QCPGraphData& prev, double step, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double py = prev.value;

    double k1 = eq->getDifY(prev);
    QCPGraphData point{t, py + step*k1};
    data->add(point);
    prev = point;
    return true;
}
