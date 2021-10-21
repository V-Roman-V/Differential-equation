#include "function.h"

Function::Function(const QString& name)
    :name(name)
{
    pen.setColor(QColor(std::rand()%245+10, std::rand()%245+10, std::rand()%245+10));
    pen.setWidthF(2);
}

QSharedPointer<QCPGraphDataContainer> Function::getData() const
{
    auto data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    double f = 4 * (double)rand()/RAND_MAX;
    for(double i = -10; i<10; i+=0.2)
        data->add({i, i*(f-i/10)});
    return data;
}

QPen Function::getPen() const
{
    return pen;
}

QString Function::getName() const
{
    return name;
}
