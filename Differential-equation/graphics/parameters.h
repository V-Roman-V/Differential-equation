#ifndef BASELINE_H
#define BASELINE_H

#include "function.h"

class Parameters : public Function
{
public:
    Parameters();
    bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const override;

    void setBasePoint(const QCPGraphData &value);
    void setStep(double value);

    QCPGraphData base();
    double       step();

private:
    QCPGraphData base_point;
    double _step;
};

#endif // BASELINE_H
