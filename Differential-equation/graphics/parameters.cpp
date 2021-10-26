#include "parameters.h"

Parameters::Parameters()
    : Function("Base point", QColor(216,102,51)),
      base_point(1,0.5),
      _step(0.4)
{
    scatter_style = QCPScatterStyle::ssCircle;
    pen.setWidthF(1);
}

bool Parameters::pointGenerator(double, QSharedPointer<QCPGraphDataContainer>& data) const
{
    double x = base_point.key, y = base_point.value;
    data->add({x,-1e5});
    data->add({x,   y});
    data->add({x, 1e5});
    return false;
}

void Parameters::setBasePoint(const QCPGraphData &value)
{
    base_point = value;
}
void Parameters::setStep(double value)
{
    _step = value;
}

QCPGraphData Parameters::base() const
{
    return base_point;
}

double Parameters::step() const
{
    return _step;
}

bool Parameters::positive() const
{
    return _positive;
}

bool Parameters::negative() const
{
    return _negative;
}

void Parameters::setNegative(bool negative)
{
    _negative = negative;
}

void Parameters::setPositive(bool positive)
{
    _positive = positive;
}
