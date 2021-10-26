#include "parameters.h"

Parameters::Parameters()
    : Function("Base point"),
      base_point(1,0.5),
      _step(0.4)
{
    scatter_style = QCPScatterStyle::ssCircle;
    pen.setWidthF(1);
    pen.setColor(QColor(216,102,51));
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

QCPGraphData Parameters::base()
{
    return base_point;
}

double Parameters::step()
{
    return _step;
}
