#ifndef LTERROR_H
#define LTERROR_H

#include "function.h"

class LTError : public Function
{
public:
    LTError(const QString& name);
    virtual ~LTError() = default;

    QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const override;
    void setData(const QSharedPointer<QCPGraphDataContainer> &value);

protected:
    QSharedPointer<QCPGraphDataContainer> data;

private:
    // We need to define the function, since it is purely virtual
    bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const override;
};

#endif // LTERROR_H
