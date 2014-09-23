#include "cell.h"

#include <QTableWidgetItem>

Cell::Cell()
{
    setDirty();
}
QTableWidgetItem &Cell::clone() const
{
    return new Cell(*this);
}
void Cell::setFormula(const QString &formula)
{
    setData(Qt::EditRole,formula);
}
QString Cell::formula() const
{
    return data(Qt::EditRole.toString());
}
void Cell::setData(int role, const QVariant &value)
{
    QTableWidgetItem::setData(role, value);
    if(role == Qt::EditRole)
        setDirty();
}
void Cell::setDirty()
{
    cacheIsDirty = true;
}
QVariant Cell::data(int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(value().isValid())
        {
            return value().toString();
        }
        else
        {
            return "####";
        }
    }
    else if(role == Qt::TextAlignmentRole)
    {
        if(value().type() == QVariant::String)
        {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
        else if
        {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    else
    {
        return QTableWidgetItem::data(role);
    }
}
//***************************************************************
//8
//88
//888
//P75
const QVariant Invalid;
QVariant Cell::value() const
{

}
QVariant Cell::evalExpression(const QString &str, int &pos) const
{

}
QVariant Cell::evalTerm(const QString &str, int &pos) const
{

}
QVariant Cell::evalFactor(const QString &str, int &pos) const
{

}
























