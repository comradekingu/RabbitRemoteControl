//! @author: Kang Lin(kl222@126.com)

#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QtGlobal>
#include <QSharedPointer>
#if defined(Q_OS_ANDROID)
    #include <QtAndroid>
#endif

#include "RabbitCommonTools.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonLog.h"
#include "FrmUpdater/FrmUpdater.h"
#ifdef BUILD_QUIWidget
    #include "QUIWidget/QUIWidget.h"
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#if defined(Q_OS_ANDROID) && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    QtAndroid::hideSplashScreen();
#endif
    
#if defined (_DEBUG) || !defined(BUILD_SHARED_LIBS)
    Q_INIT_RESOURCE(translations_RabbitRemoteControlApp);
#endif

    QApplication::setApplicationVersion(BUILD_VERSION);
    QApplication::setApplicationName("RabbitRemoteControl");
#if QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    QApplication::setDesktopFileName(QLatin1String("RabbitRemoteControl.desktop"));
#endif

    QApplication a(argc, argv);

    RabbitCommon::CTools::Instance()->Init();

    // Install translator
    QTranslator tApp;
    tApp.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
              + QDir::separator() + "RabbitRemoteControlApp_"
              + QLocale::system().name() + ".qm");
    a.installTranslator(&tApp);
    LOG_MODEL_INFO("Main", "Language: %s", QLocale::system().name().toStdString().c_str());

    a.setApplicationDisplayName(QObject::tr("Rabbit Remote Control"));
    a.setOrganizationName(QObject::tr("Kang Lin studio"));
    
    // Check update version
    QSharedPointer<CFrmUpdater> pUpdate(new CFrmUpdater());
    pUpdate->SetTitle(QImage(":/image/App"));
    if(pUpdate->GenerateUpdateXml())
        LOG_MODEL_ERROR("main", "GenerateUpdateXml fail");
    else    
        return 0;

    MainWindow* w = new MainWindow();
    //w->setWindowIcon(QIcon(":/image/App"));
    //w->setWindowTitle(a.applicationDisplayName());
    
#ifdef BUILD_QUIWidget
    QSharedPointer<QUIWidget> quiwidget(new QUIWidget(nullptr, true));
    bool check = quiwidget->connect(w, SIGNAL(sigFullScreen()),
                                    SLOT(showFullScreen()));
    Q_ASSERT(check);
    check = quiwidget->connect(w, SIGNAL(sigShowNormal()),
                               SLOT(showNormal()));
    Q_ASSERT(check);
    //quiwidget.setPixmap(QUIWidget::Lab_Ico, ":/image/App");
    //quiwidget.setTitle(a.applicationDisplayName());
    quiwidget->setMainWidget(w);
    quiwidget->show();
#else
    w->show();
#endif
    
    int nRet = a.exec();
#ifndef BUILD_QUIWidget
    delete w;
#endif

    RabbitCommon::CTools::Instance()->Clean();
    a.removeTranslator(&tApp);
#if defined (_DEBUG) || !defined(BUILD_SHARED_LIBS)
    Q_CLEANUP_RESOURCE(translations_RabbitRemoteControlApp);
#endif
    
    return nRet;
}
