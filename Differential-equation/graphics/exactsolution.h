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
    bool pointGenerator(double t, double step, QSharedPointer<QCPGraphDataContainer>& data) const override;

private:
    std::function<double(double)> y;
    std::function<double(double,double)> difY;
    std::vector<double> infDisc;
    std::vector<double> otherDisc;
};

#endif // EXACTSOLUTION_H
