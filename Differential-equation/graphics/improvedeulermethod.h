#ifndef IMPROVEDEULERMETHOD_H
#define IMPROVEDEULERMETHOD_H

#include "approximationmethod.h"

class ImprovedEulerMethod : public ApproximationMethod
{
public:
    ImprovedEulerMethod(ExactSolution* eq, Parameters* p);

protected:
    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    QCPGraphData pointGenerator(double t, const QCPGraphData& prev, double step) const override;
};

#endif // IMPROVEDEULERMETHOD_H
