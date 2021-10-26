#include "lterror.h"

LTError::LTError(const QString& name)
    : Function(name)
{}

QSharedPointer<QCPGraphDataContainer> LTError::getData(const QCPRange &) const
{
    return data;
}

void LTError::setData(const QSharedPointer<QCPGraphDataContainer> &value)
{
    data = value;
}

bool LTError::pointGenerator(double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
