#include "exactsolution.h"

ExactSolution::ExactSolution()
    :Function("Exact", QColor(10,10,10))
{}

bool ExactSolution::pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const
{
    while(1){
        // if array is empty
        if(data->size() == 0)break;

        // finding a step by subtracting from the previous one
        double step = abs(data->at(data->size()-1)->key - t);

        // If the discontinuation point, then put a vertical line
        if(abs(t+1) > step/2)break;
        data->add({-1-1e-5, -1e5});
        data->add({-1+1e-5,  1e5});
        return true;
    }
    data->add({t, getY(t)});
    return true;
}

std::vector<double> ExactSolution::pointDiscY() const
{
    return {-1,0};
}

double ExactSolution::getY(double x) const
{
    //if(abs(x+1)<1e-5) return 0; // point of discontinuity
    return 1./(x+1);
}

double ExactSolution::getDifY(const QCPGraphData& p) const
{
    double x = p.key, y = p.value;
//    if(abs(x)<1e-5) return 0; // point of discontinuity
    return y*(y-1)/x;
}
