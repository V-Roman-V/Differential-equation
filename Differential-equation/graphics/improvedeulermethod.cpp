#include "improvedeulermethod.h"

ImprovedEulerMethod::ImprovedEulerMethod(ExactSolution* eq, Parameters* p)
    : ApproximationMethod("Improved Euler",eq, p)
{
    pen.setColor(QColor(161,40,90));
}


bool ImprovedEulerMethod::leftGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double step = p->step();
    double px = prev.key, py = prev.value;

    double k1 = eq->getDifY(prev);
    double k2 = eq->getDifY({px - step/2, py - step/2*k1});

    QCPGraphData point{t, py - step*k2};
    data->add(point);
    prev = point;
    return true;
}

bool ImprovedEulerMethod::rightGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer> &data) const
{
    double step = p->step();
    double px = prev.key, py = prev.value;

    double k1 = eq->getDifY(prev);
    double k2 = eq->getDifY({px + step/2, py + step/2*k1});

    QCPGraphData point{t, py + step*k2};
    data->add(point);
    prev = point;
    return true;
}
