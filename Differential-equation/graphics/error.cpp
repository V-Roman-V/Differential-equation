#include "error.h"

Error::Error(const QString& name)
    : Function(name)
{
    data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
}

QSharedPointer<QCPGraphDataContainer> Error::getData(const QCPRange &) const
{
    return data;
}

void Error::setData(const QSharedPointer<QCPGraphDataContainer> &value)
{
    data.clear();
    data = value;
}

bool Error::pointGenerator(double, double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
