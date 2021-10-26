#ifndef MAXLTE_H
#define MAXLTE_H

#include "function.h"

class MaxLTE : public Function
{
public:
    MaxLTE(const QString& name);
    virtual ~MaxLTE() = default;

    QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const override;
    void setData(const QSharedPointer<QCPGraphDataContainer> &value);

protected:
    QSharedPointer<QCPGraphDataContainer> data;

private:
    // We need to define the function, since it is purely virtual
    bool pointGenerator(double t, double step, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // MAXLTE_H
