//! @author: Kang Lin(kl222@126.com)

#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include "ConnecterLibVnc.h"

namespace Ui {
class CDlgSettingsLibVnc;
}

class CDlgSettingsLibVnc : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgSettingsLibVnc(CConnecterLibVnc *pConnecter, QWidget *parent = nullptr);
    virtual ~CDlgSettingsLibVnc();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    
    void on_cbCompressAutoSelect_stateChanged(int arg1);

    void on_cbCompress_stateChanged(int arg1);
    void on_cbJPEG_stateChanged(int arg1);
    
    void on_pbShow_clicked();
    
private:
    Ui::CDlgSettingsLibVnc *ui;
    CConnectLibVnc::strPara* m_pPara;
};

#endif // DLGSETTINGS_H
