#include "function.h"

Function::Function(const QString& name)
    : Function(name, QColor(std::rand()%245+10, std::rand()%245+10, std::rand()%245+10))
{}

Function::Function(const QString &name, const QColor &color)
    : name(name),
      scatter_style(QCPScatterStyle::ssNone)
{
    pen.setColor(color);
    pen.setWidthF(2);
}

QSharedPointer<QCPGraphDataContainer> Function::getData(const QCPRange& range) const
{
    auto data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    double step = std::min(range.size()/200, 1.);
    for(double i = range.lower-step; i<range.upper+step; i+=step)
        if(!pointGenerator(i, step, data))break;
    return data;
}

void Function::setPen(const QPen &value)
{
    pen = value;
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
