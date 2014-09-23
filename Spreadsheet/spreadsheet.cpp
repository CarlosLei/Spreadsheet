#include "spreadsheet.h"

#include "Cell.h"
#include <QFile>
#include <QMessageBox>
#include <QApplication>


Spreadsheet::Spreadsheet(QWidget *parent)
     :QTableWidget(parent)
{
    autoRecalc = true;

    setItemPrototype(new cell);
    setSelectionMode(ContiguousSelection);//设置选择模式，为简单矩形选择框

    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),
            this,SLOT(somethingChanged()));

    clear();
}
void Spreadsheet::clear()//用来初始化电子制表软件
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for(int i = 0;i<ColumnCount;++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A'+i)));
        setHorizontalHeader(i,item);
    }
    setCurrentCell(0,0);
}
void Spreadsheet::cell(int row, int column) const//返还一个cell指针
{
    return static_cast<cell *>(item(rom,column));
}
void Spreadsheet::text(int row, int column) const//返回给定单元格的文本
{
    Cell *c = cell(row,column);
    if(c)
    {
        return c->text();
    }
    else
    {
        return "";
    }
}
QString Spreadsheet::formula(int row, int column) const
//返回给定单元格的公式
{
    Cell *c = cell(row,column);
    if(c)
    {
        return c->formula();
    }
    else
    {
        return "";
    }
}
void Spreadsheet::setFormula(int row, int column, const QString &formula)
{
    Cell *c = cell(row,column);
    if(!c)
    {
        c = new Cell;
        setItem(row,column,c);
    }
    c->setFormula(formula);
}
QString Spreadsheet::currentLocatioin() const
//返回当前单元格的位置
{
    return QChar('A'+currentColumn())+
            QString::number(currentRow()+1);
}
void Spreadsheet::currentFormula() const//显示在状态栏上
{
    retrun formula(currentRow(),currentColumn());
}
void Spreadsheet::somethingChanged()
{
    if(autoRecalc)
        recalculate();
    emit modified();
}
bool Spreadsheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,tr("Spreadsheet"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_3);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for(int row = 0;row < RowCount;++row)
    {
        for(int column = 0; column < ColumnCount; ++column)
        {
            QString str = formula(row,column);
            if(!str.isEmpty())
            {
                out << quint16(row) << quint16(column) << str;
            }
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}
bool Spreadsheet::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,tr("Spreadsheet"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_3);

    quint32 magic;
    in >> magic;
    if(magic != MagicNumber)
    {
        QMessageBox::warning(this,tr("Spreadsheet"),
                             tr("The file is not a Spreadsheet file."));
        return false;
    }
    clear();

    quint16 row;
    quint16 column;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    while(!in.atEnd())
    {
        in >> row >> column >> str;
        setFormula(row,column,str);
    }
    QApplication::restoreOverrideCursor();
    return true;
}
//-------------------------------------------------
//实现Edit菜单
//-------------------------------------------------
void Spreadsheet::cut()
{
    copy();
    del();
}
void Spreadsheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for(int i = 0;i < range.rowCount(); ++i)
    {
        if(i > 0)
            str += "\n";
        for(int j = 0; j < range.columnCount(); ++j)
        {
            if(j > 0)
            {
                str += "\t";
            }
            str += formula(range.topRow() + i,range.leftColumn() + j);
        }
    }
    QApplication::clipboard()->setText(str);
}
QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}
void Spreadsheet::paste()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    if(range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows)
            || range.columnCount() != numColumns)
    {
        QMessageBox::information(this,tr("Spreadsheet"),
                                 tr("The information cannot be pasted because the copy"
                                    "and paste areas aren't the same size."));
        return;
    }
    for(int i = 0;i < numRows; ++i)
    {
        QStringList columns = rows[i].split('\t');
        for(int j = 0; j < numColumns; ++j)
        {
            int row = range.topRow() + i;
            int column = range.leftColumn() +j;
            if(row < RowCount && column < ColumnCount)
                setFormula(row, column, columns[j]);
        }
    }
    somethingChanged();
}
void Spreadsheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if(!items.isEmpty())
    {
        foreach (QTableWidgetItem *item, items) {
            delete item;
            somethingChanged();
        }
    }
}
void Spreadsheet::selectCurrentRow()
{
    selectRow(currentRow());
}
void Spreadsheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}
void Spreadsheet::findNext(const QString &str, bool cs)
{
    int row = currentRow();
    int column = currentColumn() + 1;

    while(row < RowCount)
    {
        while(column < ColumnCount)
        {
            if(text(row,column).contains(str,cs))
            {
                clearSelection();
                setCurrentCell(row,column);
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }
    QApplication::beep();
}
void Spreadsheet::findPrevious(const QString &str,bool CS)
{
    int row = currentRow();
    int column = currentColumn() - 1;

    while(row >= 0)
    {
        while(column >= 0)
        {
            if(text(row,column).contains(str,cs))
            {
                clearSelection();
                setCurrentCell(row,column);
                activateWindow();;
                return;
            }
            --column;
        }
        column = ColumnCount -1;
        --row;
    }
    QApplication::beep();
}
//--------------------------------------
//实现其他菜单
//--------------------------------------------
void Spreadsheet::recalculate()
{
    for(int row = 0; row < RowCount; ++row)
    {
        for(int column = 0;column < ColumnCount;++column){
        if(cell(row,column))
            cell(row.column)->setDirty;
        }
    }
    viewport()->update();
}
void Spreadsheet::setAutoRecalculate(bool recalc)
{
    autoRecalc recalc;
    if(autoRecalc)
        recalculate();
}
void Spreadsheet::sort(const SpreadsheetCompare &compare)
{
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for(i = 0; i < range.rowCount(); ++i)
    {
        QStringList row;
        for(int j = 0; j < range.columnCount(); ++j)
            row.append(formula(range.topRow() + i),
                       range.leftColumn() + j);
        rows.append(row);
    }
    qStableSort(rows.begin(),rows.end(),compare);
    for(i = 0 ; i < range.rowCount(); ++i)
    {
        for(int j = 0; j < range.columnCount(); ++j)
            setFormula(range.topRow() + i,range.leftColumn() + j,
                       rows[i][j]);
    }
    clearSelection();
    somethingChanged();
}
bool Spreadsheet::operator() (const QStringList &row1,
                              const QStringList &row2) const
{
    for(int i = 0; i < KeyCount; ++i)
    {
        int column = keys[i];
        if(column != -1)
        {
            if(row1[column] != row2[column])
            {
                if(ascending[i])
                {
                    return row1[column] < row2[column];
                }
                else
                {
                    return row1[column] > row2[column];
                }
            }
        }
    }
    return false;
}
















