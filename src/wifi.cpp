#include "wifi.h"
#include <src/wsettings.h>
#include <iostream>
Wifi::Wifi()
{
}

/**
*lzjqsdd
*/
bool Wifi::startWifi()
{
    WSettings m_settings;
    QString _g = "-g";
    QString __no_virt = "--no-virt";
    QString __deamon = "--daemon";

    QStringList args = QStringList() << m_settings.Interface_Create()
                                     << m_settings.Interface_Shared() << m_settings.APName()
                                     << m_settings.Password()
                                     << _g << m_settings.AccessPoint();

    //use --no-virt option if shared interface is different from create_interface
    // this option will be moved to high-level configuration(maybe in version2.0)
    if(m_settings.Interface_Create() != m_settings.Interface_Shared())
        args << __no_virt;

    //default to run wifiassist in deamon mode.
    args << __deamon;

    //use pkexec for first version,there is some questions unsolved with gksu.
    if(!QProcess::startDetached(m_settings.path_exec(),args))
    {
        return false;
    }
    else
    {
        return true;
    }
}
/**
*lzjqsdd
*/
bool Wifi::stopWifi()
{
    WSettings m_settings ;
    QString arg1 = "--stop";
    QStringList args = QStringList() <<arg1<<m_settings.Interface_Create();
    if(!QProcess::startDetached(m_settings.path_exec(),args))
    {
        return false;
    }
    else
        return true;
}

/*
 * use when update config,e.g. change wifi name or password or access point
*/
void Wifi::restartWifi()
{
    stopWifi();
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<3000)
        QCoreApplication::processEvents();
    startWifi();
}


