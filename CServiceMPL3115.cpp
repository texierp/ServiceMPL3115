#include "CServiceMPL3115.h"

CServiceMPL3115::CServiceMPL3115():
    m_timer(NULL),
    m_temperature(0),
    m_pressure(0)
{
    /**
      * DBUS INIT
      **/
    if (!QDBusConnection::systemBus().isConnected())
    {
        qDebug() << "DBUS not started !";
    }
    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME))
    {
        qDebug() << "Already Registered !";
    }

    QDBusConnection::systemBus().registerObject(PROPERTY_PATH,
                                               this,
                                               QDBusConnection::ExportAllInvokables);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &CServiceMPL3115::eventLoop);
    m_timer->start(1000);
}

CServiceMPL3115::~CServiceMPL3115()
{
    delete m_timer;
}

/**
 * @brief CServiceMPL3115::getTemperature
 * @return
 */
double CServiceMPL3115::getTemperature() const
{
    return m_temperature;
}

/**
 * @brief CServiceMPL3115::getPressure
 * @return
 */
double CServiceMPL3115::getPressure() const
{
    return m_pressure;
}

/**
 * @brief CServiceMPL3115::readValueFromFile
 * @param filePath
 * @return
 */
QByteArray CServiceMPL3115::readValueFromFile(QString filePath)
{
    QByteArray data;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        data.remove(data.length() - 1, 1);
        file.close();
    }
    else qDebug()<<"Error while opening "<<filePath;

    return data;
}

void CServiceMPL3115::eventLoop()
{
    QByteArray rawTemp = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp_raw");
    QByteArray scaleTemp = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp_scale");

    m_temperature = rawTemp.toInt() * scaleTemp.toDouble();

    qDebug()<<m_temperature;

}
