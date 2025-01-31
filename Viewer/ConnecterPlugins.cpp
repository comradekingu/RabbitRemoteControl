//! @author: Kang Lin (kl222@126.com)

#include "ConnecterPlugins.h"
#include <QDebug>
#include "ConnectThread.h"
#include "RabbitCommonLog.h"

#ifdef BUILD_QUIWidget
    #include "QUIWidget/QUIWidget.h"
#endif

CConnecterPlugins::CConnecterPlugins(CPluginFactory *parent)
    : CConnecter(parent),
      m_bExit(false),
      m_pThread(nullptr),
      m_pView(new CFrmViewer()),
      m_pParameter(nullptr)
{}

CConnecterPlugins::~CConnecterPlugins()
{
    if(m_pThread)
    {
        m_pThread->wait();
        delete m_pThread;
    }

    if(m_pView)
        delete m_pView;
    
    qDebug() << this << this->metaObject()->className();
}

const QString CConnecterPlugins::Name()
{
    if(m_pParameter && !m_pParameter->szName.isEmpty())
        return m_pParameter->szName;
    return ServerName();
}

QWidget *CConnecterPlugins::GetViewer()
{
    return m_pView;
}

int CConnecterPlugins::OnRun()
{
    //LOG_MODEL_DEBUG("CConnecterBackThread", "Current thread: 0x%X", QThread::currentThreadId());
    int nRet = -1;
    CConnect* pConnect = InstanceConnect();
    
    do{
        CConnect* pConnect = InstanceConnect();
        if(nullptr == pConnect) break;
        
        nRet = pConnect->Initialize();
        if(nRet) break;
        
        /**
          nRet < 0 : error
          nRet = 0 : emit sigConnected
          nRet = 1 : emit sigConnected in CConnect
          */
        nRet = pConnect->Connect();
        if(nRet < 0) break;
        if(0 == nRet) emit sigConnected();

        while (!m_bExit) {
            try {
                // 0 : continue
                // 1: exit
                // < 0: error
                int nRet = pConnect->Process();
                if(nRet) break;
            }  catch (...) {
                LOG_MODEL_ERROR("ConnecterBackThread", "process fail:%d", nRet);
                break;
            }
        }
        
    }while (0);

    emit sigDisconnected();

    pConnect->Clean();
    delete pConnect;
    qDebug() << "CConnecterPlugins::OnRun() end";
    return nRet;
}

int CConnecterPlugins::Connect()
{
    int nRet = 0;
    m_pThread = new CConnectThread(this);
    if(m_pThread)
        m_pThread->start();
    
    nRet = OnConnect();
    return nRet;
}

int CConnecterPlugins::DisConnect()
{
    int nRet = 0;
    m_bExit = true;
    nRet = OnDisConnect();
    
    return nRet;
}

int CConnecterPlugins::OnConnect()
{
    return 0;
}

int CConnecterPlugins::OnDisConnect()
{
    emit sigDisconnected();
    return 0;
}

QString CConnecterPlugins::ServerName()
{
    if(m_szServerName.isEmpty())
    {
        if(m_pParameter && !m_pParameter->szHost.isEmpty())
            m_szServerName = m_pParameter->szHost + ":"
                    + QString::number(m_pParameter->nPort);
        else
            return CConnecter::Name();
    }
    return CConnecter::ServerName();
}

int CConnecterPlugins::Load(QDataStream &d)
{
    int nRet = 0;
    Q_ASSERT(m_pParameter);
    qint16 version = 0;
    d >> version 
            >> *m_pParameter;

    nRet = OnLoad(d);
    return nRet;
}

int CConnecterPlugins::Save(QDataStream &d)
{
    int nRet = 0;
    Q_ASSERT(m_pParameter);
    d << Version()
      << *m_pParameter;
    
    nRet = OnSave(d);
    return nRet;
}

int CConnecterPlugins::OnLoad(QDataStream& d)
{
    Q_UNUSED(d);
    return 0;
}

int CConnecterPlugins::OnSave(QDataStream& d)
{
    Q_UNUSED(d);
    return 0;
}

int CConnecterPlugins::OpenDialogSettings(QWidget *parent)
{
    int nRet = -1;
    QDialog* p = GetDialogSettings(parent);
    if(p)
    {
        p->setWindowIcon(this->Icon());
#ifdef BUILD_QUIWidget
        QUIWidget* quiwidget = new QUIWidget();
        quiwidget->setMainWidget(p);
        bool check = connect(p, SIGNAL(accepted()), quiwidget, SLOT(accept()));
        Q_ASSERT(check);
        check = connect(p, SIGNAL(rejected()), quiwidget, SLOT(reject()));
        Q_ASSERT(check);
        p = quiwidget;
#endif
        
        p->setAttribute(Qt::WA_DeleteOnClose);
        nRet = p->exec();
    } else {
        LOG_MODEL_ERROR("CConnecter",  "The protol[%s] don't settings dialog", Protol().toStdString().c_str());
    }
    return nRet;
}
