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
    void setPositive(bool positive);
    void setNegative(bool negative);

    QCPGraphData base()  const;
    double       step()  const;
    QCPRange     range() const;
    bool         positive() const;
    bool         negative() const;

private:
    QCPGraphData base_point;
    double _step;
    bool _positive;
    bool _negative;
};

#endif // BASELINE_H
