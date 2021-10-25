#ifndef EULERMETHOD_H
#define EULERMETHOD_H

#include "approximationmethod.h"

class EulerMethod : public ApproximationMethod
{
public:
    EulerMethod(ExactSolution* eq, Parameters* p);

protected:
    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    bool leftGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const override;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    bool rightGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // EULERMETHOD_H
