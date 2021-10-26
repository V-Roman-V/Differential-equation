#ifndef IMPROVEDEULERMETHOD_H
#define IMPROVEDEULERMETHOD_H

#include "approximationmethod.h"

class ImprovedEulerMethod : public ApproximationMethod
{
public:
    ImprovedEulerMethod(ExactSolution* eq, Parameters* p);

protected:
    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    bool leftGenerator(double t, QCPGraphData& prev, double step, QSharedPointer<QCPGraphDataContainer>& data) const override;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    bool rightGenerator(double t, QCPGraphData& prev, double step, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // IMPROVEDEULERMETHOD_H
