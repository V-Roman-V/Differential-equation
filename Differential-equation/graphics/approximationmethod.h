#ifndef APPROXIATIONMETHOD_H
#define APPROXIATIONMETHOD_H

#include "function.h"
#include "parameters.h"
#include "exactsolution.h"
#include "error.h"
#include <limits>

class ApproximationMethod : public Function
{
public:
    ApproximationMethod(const QString& name, ExactSolution* eq, Parameters* p);

    QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const override;

    Error *getLte();
    Error *getMaxlte();
    Error *getGte();
    Error *getMaxgte();

    void updateErrors(const QCPRange& range, double min, double max, double shift);

protected:
    QSharedPointer<QCPGraphDataContainer> calculateData(const QCPRange& range, double step, bool useExact) const;
    QSharedPointer<QCPGraphDataContainer> calculateLTE(const QCPRange& range, double step, bool update);
    QSharedPointer<QCPGraphDataContainer> calculateGTE(const QCPRange& range, double step, bool update);
    QSharedPointer<QCPGraphDataContainer> calculateMaxLTE(const QCPRange& range, double mins, double maxs, double shift, bool update);
    QSharedPointer<QCPGraphDataContainer> calculateMaxGTE(const QCPRange& range, double mins, double maxs, double shift, bool update);

    ExactSolution* eq;

    // Generate points from base to left, returns whether to continue generating. (previous data always exists)
    virtual QCPGraphData leftGenerator(double t, const QCPGraphData& prev, double step) const = 0;

    // Generate points from base to right, returns whether to continue generating. (previous data always exists)
    virtual QCPGraphData rightGenerator(double t, const QCPGraphData& prev, double step) const = 0;

private:
    Parameters* p;
    Error lte, gte;
    Error maxlte, maxgte;
private:
    // We need to define the function, since it is purely virtual
    bool pointGenerator(double t, double step, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // APPROXIATIONMETHOD_H
