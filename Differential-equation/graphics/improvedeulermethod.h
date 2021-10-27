#ifndef IMPROVEDEULERMETHOD_H
#define IMPROVEDEULERMETHOD_H

#include "approximationmethod.h"

class ImprovedEulerMethod : public ApproximationMethod
{
public:
    ImprovedEulerMethod(ExactSolution* eq, Parameters* p);

protected:
    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    QCPGraphData leftGenerator(double t, const QCPGraphData& prev, double step) const override;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    QCPGraphData rightGenerator(double t, const QCPGraphData& prev, double step) const override;
};

#endif // IMPROVEDEULERMETHOD_H
