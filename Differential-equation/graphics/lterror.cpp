#include "lterror.h"

LTError::LTError(const QString& name)
    : Function(name)
{
    data = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
}

QSharedPointer<QCPGraphDataContainer> LTError::getData(const QCPRange &) const
{
    return data;
}

void LTError::setData(const QSharedPointer<QCPGraphDataContainer> &value)
{
    data.clear();
    data = value;
}

bool LTError::pointGenerator(double, QSharedPointer<QCPGraphDataContainer> &) const
{
    return false;
}
