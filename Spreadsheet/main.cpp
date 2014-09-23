#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //--------------------------------
    //程序启动画面
    //---------------------------------
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/sea.jpg"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight|Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight,Qt::white);

    MainWindow *mainWin = new MainWindow;

    splash->showMessage(QObject::tr("Loading Modules..."),
                        topRight,Qt::white);

    //loadModules();
    qApp->processEvents();

    splash->showMessage(QObject::tr("Establishing connections..."),
                        topRight,Qt::white);
    //establishConnections();//建立连接
    qApp->processEvents();

    mainWin->show();
    splash->finish(mainWin);
    //Makes the splash screen wait
    //until the widget mainWin is displayed before calling close() on itself.
    delete splash;

    return app.exec();
}



