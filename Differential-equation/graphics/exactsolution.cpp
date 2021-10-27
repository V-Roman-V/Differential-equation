#include "exactsolution.h"

ExactSolution::ExactSolution()
    :Function("Exact", QColor(10,10,10))
{
    y    = [](double x)          { return 1./(x+1); };
    difY = [](double x, double y){ return y*(y-1)/x;};
    infDisc   = {-1}; // Infinite discontinuities
    otherDisc = {0};// all others discontinuities
}

bool ExactSolution::pointGenerator(double t, double step, QSharedPointer<QCPGraphDataContainer>& data) const
{
    // If the infinate discontinuation point, then put a vertical line
    for(double p: infDisc)
        if(abs(t-p) <= step/2){
            data->add({p - 1e-5, -1e5});
            data->add({p + 1e-5,  1e5});
            return true;
        }
    for(double p: otherDisc)
        if(abs(t-p) <= step/2)
            return true;

    data->add({t, getY(t)});
    return true;
}

std::vector<double> ExactSolution::pointDiscY() const
{
    std::vector<double> disc = infDisc;
    disc.insert(disc.end(), otherDisc.begin(), otherDisc.end());
    return disc;//{-1,0};
}

double ExactSolution::getY(double x) const
{
    return y(x);
}

double ExactSolution::getDifY(const QCPGraphData& p) const
{
    double x = p.key, y = p.value;
    return difY(x,y);
}
