#ifndef FUNCTION_H
#define FUNCTION_H

#include "QCustomPlot/qcustomplot.h"
#include<QVector>
#include<QPair>
#include<QPen>

class Function
{
public:
    Function(const QString& name);

    QString getName() const;
    QPen getPen() const;
    QSharedPointer<QCPGraphDataContainer> getData() const;

private:
    QString name;
    QPen pen;
};

#endif // FUNCTION_H
