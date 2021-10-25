#ifndef EXACTSOLUTION_H
#define EXACTSOLUTION_H

#include "function.h"
#include <algorithm>

class ExactSolution : public Function
{
public:
    ExactSolution();

    double getY(double x) const;
    std::vector<double> pointDiscY() const;
    double getDifY(const QCPGraphData& p) const;

protected:
    bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // EXACTSOLUTION_H
