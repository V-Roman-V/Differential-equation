#ifndef APPROXIATIONMETHOD_H
#define APPROXIATIONMETHOD_H

#include "function.h"
#include "parameters.h"
#include "exactsolution.h"
#include <limits>

class ApproximationMethod : public Function
{
public:
    ApproximationMethod(const QString& name, ExactSolution* eq, Parameters* p);

    QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const override;

protected:
    ExactSolution* eq;
    Parameters* p;

    // We need to define the function, since it is purely virtual
    bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const override;

    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    virtual bool leftGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const = 0;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    virtual bool rightGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const = 0;
};

#endif // APPROXIATIONMETHOD_H
