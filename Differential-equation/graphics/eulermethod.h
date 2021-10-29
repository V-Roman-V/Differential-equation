#ifndef EULERMETHOD_H
#define EULERMETHOD_H

#include "approximationmethod.h"

class EulerMethod : public ApproximationMethod
{
public:
    EulerMethod(ExactSolution* eq, Parameters* p);

protected:
    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    QCPGraphData pointGenerator(double t, const QCPGraphData& prev, double step) const override;
};

#endif // EULERMETHOD_H
