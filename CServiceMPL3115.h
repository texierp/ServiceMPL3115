#ifndef CSERVICEMPL3115_H
#define CSERVICEMPL3115_H

#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QtDBus/QDBusConnection>

#define SERVICE_NAME        "org.warp7.service.mpl3115"
#define PROPERTY_PATH       "/"

class CServiceMPL3115: public QObject
{
    Q_OBJECT
public:
    CServiceMPL3115();
    ~CServiceMPL3115();

    Q_INVOKABLE double getTemperature() const;
    Q_INVOKABLE double getPressure() const;

private:
    QByteArray readValueFromFile(QString filePath);

    QTimer *m_timer;
    double m_temperature;
    double m_pressure;

protected slots:
    void eventLoop();
};

#endif // CSERVICEMPL3115_H
