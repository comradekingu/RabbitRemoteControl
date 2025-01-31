//! @author: Kang Lin(kl222@126.com)

#ifndef CCONNECTERTIGERVNC_H
#define CCONNECTERTIGERVNC_H

#include "ConnecterPlugins.h"
#include "DlgSettingsTigerVnc.h"

class CConnecterTigerVnc : public CConnecterPlugins
{
    Q_OBJECT

public:
    explicit CConnecterTigerVnc(CPluginFactory *parent);
    virtual ~CConnecterTigerVnc() override;

    virtual qint16 Version() override;
    
    virtual int Connect() override;
    virtual int DisConnect() override;
    
protected:
    virtual QDialog* GetDialogSettings(QWidget* parent = nullptr) override;
    
    virtual int OnLoad(QDataStream& d) override;
    virtual int OnSave(QDataStream& d) override;

    virtual CConnect* InstanceConnect() override;
    
public:
    CConnectTigerVnc::strPara m_Para;
    CConnect* m_pConnect;
};

#endif // CCONNECTERTIGERVNC_H
