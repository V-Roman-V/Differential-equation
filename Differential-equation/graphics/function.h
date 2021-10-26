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
    virtual ~Function()=default;

    QString getName() const;
    QPen getPen() const;
    QCPScatterStyle getScatterStyle() const;
    virtual QSharedPointer<QCPGraphDataContainer> getData(const QCPRange& range) const;

protected:
    QString name;
    QPen pen;
    QCPScatterStyle scatter_style;


    // Generate points from left ot right, returns whether to continue generating
    virtual bool pointGenerator(double t, QSharedPointer<QCPGraphDataContainer>& data) const = 0;
};


#endif // FUNCTION_H
