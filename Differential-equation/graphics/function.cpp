#include "function.h"

Function::Function(const QString& name)
    : name(name),
      scatter_style(QCPScatterStyle::ssNone)
{
    pen.setColor(QColor(std::rand()%245+10, std::rand()%245+10, std::rand()%245+10));
    pen.setWidthF(2);

}

QSharedPointer<QCPGraphDataContainer> Function::getData(const QCPRange& range) const
{
    auto data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    double step = std::min(range.size()/200, 1.);
    for(double i = range.lower-step; i<range.upper+step; i+=step)
        if(!pointGenerator(i, data))break;
    return data;
}

QCPScatterStyle Function::getScatterStyle() const
{
    return scatter_style;
}

QPen Function::getPen() const
{
    return pen;
}

QString Function::getName() const
{
    return name;
}
