#ifndef APPROXIATIONMETHOD_H
#define APPROXIATIONMETHOD_H

#include "function.h"
#include "parameters.h"
#include "exactsolution.h"
#include "lterror.h"
#include <limits>

class ApproximationMethod : public Function
{
public:
    ApproximationMethod(const QString& name, ExactSolution* eq, Parameters* p);
    virtual ~ApproximationMethod();

    QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const override;

    LTError *getLte() const;

protected:
    ExactSolution* eq;
    Parameters* p;
    LTError* lte;

    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    virtual bool leftGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const = 0;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    virtual bool rightGenerator(double t, QCPGraphData& prev, QSharedPointer<QCPGraphDataContainer>& data) const = 0;

private:
    // We need to define the function, since it is purely virtual
    bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // APPROXIATIONMETHOD_H
