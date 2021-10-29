#include "rungekuttamethod.h"

RungeKuttaMethod::RungeKuttaMethod(ExactSolution* eq, Parameters* p)
    :ApproximationMethod("Runge Kutta",eq, p)
{
    pen.setColor(QColor(171,183,142));
}

QCPGraphData RungeKuttaMethod::pointGenerator(double t, const QCPGraphData& prev, double step) const
{
    double px = prev.key, py = prev.value;

    double k1 = eq->getDifY(prev);
    double k2 = eq->getDifY({px + step/2, py + step/2*k1});
    double k3 = eq->getDifY({px + step/2, py + step/2*k2});
    double k4 = eq->getDifY({px + step  , py + step  *k3});

    return{t, py + step/6*(k1 + 2*k2 + 2*k3 + k4)};
}
