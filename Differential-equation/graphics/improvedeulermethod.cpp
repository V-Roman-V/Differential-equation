#include "improvedeulermethod.h"

ImprovedEulerMethod::ImprovedEulerMethod(ExactSolution* eq, Parameters* p)
    : ApproximationMethod("Improved Euler",eq, p)
{
    pen.setColor(QColor(161,40,90));
}


QCPGraphData ImprovedEulerMethod::leftGenerator(double t, const QCPGraphData& prev, double step) const
{
    double px = prev.key, py = prev.value;

    double k1 = eq->getDifY(prev);
    double k2 = eq->getDifY({px - step/2, py - step/2*k1});

    return {t, py - step*k2};
}

QCPGraphData ImprovedEulerMethod::rightGenerator(double t, const QCPGraphData& prev, double step) const
{
    double px = prev.key, py = prev.value;

    double k1 = eq->getDifY(prev);
    double k2 = eq->getDifY({px + step/2, py + step/2*k1});

    return {t, py + step*k2};
}
