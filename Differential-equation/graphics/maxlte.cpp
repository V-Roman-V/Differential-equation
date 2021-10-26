#include "maxlte.h"

MaxLTE::MaxLTE(const QString& name)
    : Function(name)
{
    data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
}

QSharedPointer<QCPGraphDataContainer> MaxLTE::getData(const QCPRange &) const
{
    return data;
}

void MaxLTE::setData(const QSharedPointer<QCPGraphDataContainer> &value)
{
    data.clear();
    data = value;
}

bool MaxLTE::pointGenerator(double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
