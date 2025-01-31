//! @author: Kang Lin(kl222@126.com)

#ifndef CVIEW_H
#define CVIEW_H

#include <QWidget>
#include "Connecter.h"
#include "FrmViewScroll.h"

/**
 * @brief The CView class
 * @note The parameters and return QWidget* is same as CConnecter::GetViewer()
 */
class CView : public QWidget
{
    Q_OBJECT
public:
    explicit CView(QWidget *parent = nullptr);
    
    // QWidget* pView must is same as CConnecter::GetViewer()
    virtual int AddView(QWidget* pView) = 0;
    // QWidget* pView must is same as CConnecter::GetViewer()
    virtual int RemoveView(QWidget* pView) = 0;
    // @note The return QWidget* must is same as CConnecter::GetViewer()
    virtual QWidget* GetCurrentView() = 0;
    virtual int SetFullScreen(bool bFull) = 0;
    //The QWidget* pView must is same as CConnecter::GetViewer()
    virtual void SetWidowsTitle(QWidget* pView, const QString& szTitle) = 0;
    //The QWidget* pView must is same as CConnecter::GetViewer()
    virtual void SetAdaptWindows(CFrmViewer::ADAPT_WINDOWS aw = CFrmViewer::Original, QWidget* pView = nullptr) = 0;
    
public Q_SLOTS:
    virtual void slotSystemCombination() = 0;
    
Q_SIGNALS:
    // @note The QWidget* pView must is same as CConnecter::GetViewer()
    void sigCloseView(const QWidget* pView);
    void sigAdaptWindows(const CFrmViewer::ADAPT_WINDOWS aw);
};

#endif // CVIEW_H
