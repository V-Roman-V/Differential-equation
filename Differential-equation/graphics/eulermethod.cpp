#include "eulermethod.h"
EulerMethod::EulerMethod(ExactSolution* eq, Parameters* p)
    : ApproximationMethod("Euler",eq,p)
{
    pen.setColor(QColor(21,225,235));
}

QCPGraphData EulerMethod::pointGenerator(double t, const QCPGraphData& prev, double step) const
{
    double py = prev.value;

    double k1 = eq->getDifY(prev);
    return {t, py + step*k1};
}
