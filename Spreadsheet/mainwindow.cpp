#include "mainwindow.h"

#include <QtGui>

#include "finddialog.h"
#include "gotocell.h"
#include "sortdialong.h"
#include "spreadsheet.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QTextEdit>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);//设置关闭窗口时同时将其删除
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSetting();

    findDialog = 0;

    setWindowIcon(QIcon(":/images/smile.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{

}
//创建各种动作并且初始化
void MainWindow::createActions()
{
    //_____________________________
    //spreadsheet = new Spreadsheet();????????????????
    //_____________________________

    newAction = new QAction(tr("&New"),this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));

    openAction = new QAction(tr("&Open"),this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    saveAction = new QAction(tr("&Save"),this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"),this);
    saveAsAction->setIcon(QIcon(":/images/save-as.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save as a file"));
    connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

    closeAction = new QAction(tr("&Close"),this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("CLose this window"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));//????????????

    //添加最近的文档
    for(int i = 0;i < MaxRecentFiles; ++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),
                this,SLOT(openRecentFile()));
    }
    exitAction = new QAction(tr("E&xit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction,SIGNAL(triggered()),this,
            SLOT(closeAllWindows()));

    cutAction = new QAction(tr("&Cut"),this);
    cutAction->setIcon(QIcon(":/iamges/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut file"));
    connect(cutAction,SIGNAL(triggered()),this,SLOT(QTextEdit::cut()));
    //cut(),copy(),paste(),undo()都是存在的，这里不知道能不能直接调用
    //例如ui->text->cut()
    copyAction = new QAction(tr("&Copy"),this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy file"));
    connect(copyAction,SIGNAL(triggered()),this,SLOT(QTextEdit::copy()));

    pasteAction = new QAction(tr("&Paste"),this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste file"));
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(QTextEdit::paste()));

    deleteAction = new QAction(tr("&Delete"),this);
    //deleteAction->setIcon(QIcon(":/images/delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("delete a file"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(Delete()));
    //这里的Delete()好像用不了

    selectAllAction = new QAction(tr("&All"),this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction,SIGNAL(triggered()),spreadsheet,SLOT(selectAll()));

    selectRowAction = new QAction(tr("&Row"),this);
    selectAllAction->setStatusTip(tr("Select a row of the cells in the spreadsheet"));
    connect(selectRowAction,SIGNAL(triggered()),spreadsheet,SLOT(selectRow()));

    selectColumnAction = new QAction(tr("&Column"),this);
    selectColumnAction->setStatusTip(tr("Select a Column of the cells in the spreadsheet"));
    connect(selectColumnAction,SIGNAL(triggered()),spreadsheet,SLOT(selectColumn()));

    findAction = new QAction(tr("&Find"),this);
    findAction->setIcon(QIcon(":/images/find.png"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find  the cells"));
    connect(findAction,SIGNAL(triggered()),this,SLOT(find()));

    goToCellAction = new QAction(tr("&Go To Cell"),this);
    //goToCellAction->setIcon(QIcon(":"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Go To Cell"));
    connect(goToCellAction,SIGNAL(triggered()),this,SLOT(goToCell()));

    recalculateAction = new QAction(tr("&Recalculate"),this);
    recalculateAction->setShortcut(tr("F9"));

    sortAction = new QAction(tr("&Sort"),this);
    sortAction->setStatusTip(tr("sort..."));

    showGridAction = new QAction(tr("&Show Grid"),this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction,SIGNAL(toggled(bool)),spreadsheet,
            SLOT(setShowGrid(bool)));

    autoRecalcAction = new QAction(tr("&Auto-Recalculate"),this);
    autoRecalcAction->setCheckable(true);

    aboutQtAction = new QAction(tr("About Qt"),this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    aboutAction = new QAction(tr("&About"),this);
    aboutAction->setStatusTip(tr("Show the Qt what waht??"));

}
//建立菜单栏并将动作都添加到菜单栏里
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(closeAction);
    separatorAction = fileMenu->addSeparator();
    for(int i = 0;i<MaxRecentFiles; ++i)
    {
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}
//建立context上下文（右键）操作
void MainWindow::createContextMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}
//建立工具栏并把需要的动作添加进去
void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}
//设置状态栏
void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("W999");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel,1);//stretch used to compute a suitable size
                                      //伸展因子1
    connect(spreadsheet,SIGNAL(currentCellChanged(int,int,int,int)),this,
            SLOT(updateStatusBar()));
    connect(spreadsheet,SIGNAL(modified()),
            this,SLOT(spreadsheetModified()));
    updateStatusBar();
}
void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocatioin());
    locationLabel->setText(spreadsheet->currentFormula());
}
void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

//实现File文件
void MainWindow::newFile()//新建文件
{
    /*if(okToContinue())
    {
        spreadsheet->clear();
        setCurrentFile("");
    }*/
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}
bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this,tr("Spreadsheet"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes|QMessageBox::No
                                     |QMessageBox::Cancel);
        if(r == QMessageBox::Yes)
        {
            return save();
        }
        else if(r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}
void MainWindow::open()
{
    if(okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Spreadsheet"),
                                                        ".",
                                                        tr("Spreadsheet files(*.sp)"));
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}
bool MainWindow::loadFile(const QString &fileName)
{
    if(!spreadsheet->readFile(fileName))
    {
        statusBar()->showMessage(tr("Loading canceled"),2000);
        //hide 2000 milli-seconds timeout
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"),2000);
    return true;
}
bool MainWindow::save()
{
    if(curFile.isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}
bool MainWindow::saveFile(const QString &fileName)
{
    if(!spreadsheet->writeFile(fileName))
    {
        statusBar()->showMessage(tr("Saving canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"),2000);
    return true;
}
bool MainWindow::saveAs()
{
    QString filenName = QFileDialog::getSaveFileName(this,
                       tr("Save Spreadsheet"),
                            ".",
                      tr("Spreadsheet file (*.sp)"));
    if(filenName.isEmpty())
    {
        return false;
    }
    return saveFile(filenName);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue())
    {
        writeSetting();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);
    QString shownName = tr("Untitled");
    if(!curFile.isEmpty())
    {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);//除掉文件列表中使用过的文件
        recentFiles.prepend(curFile);//将文件添加到第一项
        updateRecentFileActions();
    }
   // setWindowTitle(tr("%1[*]-%2").arg(shownName).arg(tr("Spreadsheet")));
}
QString MainWindow::strippedName(const QString &fullFileName)//去掉文件名中的路径字符
{
    return QFileInfo(fullFileName).fileName();
}
void MainWindow::updateRecentFileActions()//更新File菜单中的那些条目
{
    QMutableStringListIterator i(recentFiles);
    //使用Java风格的迭代器，可以移除任何不再存在的文件
    while(i.hasNext())//存在下一个
    {
        if(!QFile::exists(i.next()))
            i.remove();//删除不存在的
    }
    for(int j = 0;j < MaxRecentFiles; ++j)
    {
        if(j<recentFiles.count())
        {
            QString text = tr("&%1 %2")
                    .arg(j+1)
                    .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());//分隔符可见若现有文档有
}
void MainWindow::openRecentFile()
{
    if(okToContinue())
    {
        QAction *action = qobject_cast<QAction *>(sender());
        //动态类型强制转换，把sender()转换成QAction指针，返回true,oherwise false
        if(action)
            loadFile(action->data().toString());
    }
}
//-----------------------------------------------
//实现使用对话框
//-----------------------------------------------
void MainWindow::find()//查找
{
    if(!findDialog)
    {
        //caseinsensitive 不分大小写
        findDialog = new FindDialog(this);
        connect(findDialog,SIGNAL(findNext(const QString &,
                                           Qt::CaseSensitivity)),
                spreadsheet,SLOT(findNext(const QString &,
                                          Qt::CaseSensitivity)));
        connect(findDialog,SIGNAL(findPrevious(const QString &,
                                               Qt::CaseSensitivity)),
                spreadsheet,SLOT(findPrevious(const QString &,
                                          Qt::CaseSensitivity)));
    }
    findDialog->show();
    findDialog->raise();//放在最前
    findDialog->activateWindow();//选择为当前活动窗口
}

void MainWindow::goToCell()//去到所在单元
{
    GoToCell *dialog = new GoToCell(this);
    if(dialog->exec())//以模态打开对话框,返回accept=1，ignored=0
    {
        QString str = dialog->lineEdit->text().toUpper();//变成大写
        spreadsheet->setCurrentCell(str.mid(1).toInt()-1,
                                    str[0].unicode()-'A');//得到行列号

    }
    delete dialog;
}
void MainWindow::sort()//排列
{
    SortDialong dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A'+range.leftColumn(),
                          'A'+range.rightColumn());
    if(dialog.exec())
    {
        SpreadsheetCompare compare;
        compare.keys[0] =
                dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] =
                dialog.secondaryColumnCombo->currentIndex()-1;
        compare.keys[2] =
                dialog.tertiaryColumnCombo->currentIndex() -1;

        compare.ascending[0] =
                (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] =
                (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] =
                (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spreadsheet->sort(compare);
    }
    //这里又是这个问题，用UI设计的界面怎么添加到你的主应用程序中
}
void MainWindow::about()//绝大多数about对话框形式
{
    QMessageBox::about(this,tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1</h2>"
                          "<p>Copyright &copy; 2008 Software Inc."
                          "<p>Spreadsheet is a small application that"
                          "demonstrates QAction, QMainWindow, QMenuBar,"
                          "QStatusBar, QTableWidget, QToolBar, and many other"
                          "Qt classes."));

}
//-----------------------------------------------
//存储设置
//------------------------------------------------
void MainWindow::writeSetting()//保存应用程序的设置
{
    QSettings settings("Software Inc.","Spreadsheet");
                      //format          application
    settings.setValue("geometry",saveGeometry());
    settings.setValue("recentFiles",recentFiles);
    settings.setValue("showGrid",showGridAction->isCheckable());
    settings.setValue("autoRecalc",autoRecalcAction->isCheckable());
}
void MainWindow::readSetting()//载入应用程序的那些设置
{
    QSettings settings("Software Inc.","Spreadsheet");
    restoreGeometry(settings.value("geometry").toByteArray());
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid",true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc",true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}














