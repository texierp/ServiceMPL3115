#include "CServiceMPL3115.h"

CServiceMPL3115::CServiceMPL3115():
    m_timer(NULL),
    m_temperature(0),
    m_pressure(0),
    m_enabled(false)
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

/**
 * @brief CServiceMPL3115::~CServiceMPL3115
 */
CServiceMPL3115::~CServiceMPL3115()
{
    if (m_timer->isActive())
        m_timer->stop();
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
 * @brief CServiceMPL3115::enableLoop
 * @param value
 */
void CServiceMPL3115::enableLoop(bool value)
{
    m_enabled = value;
}

/**
 * @brief CServiceMPL3115::loopIsEnabled
 * @return
 */
bool CServiceMPL3115::loopIsEnabled()
{
    return m_enabled;
}

/**
 * @brief CServiceMPL3115::readValueFromFile
 * @param filePath
 * @return
 */
qint8 CServiceMPL3115::readValueFromFile(QString filePath, QByteArray &data)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        data.remove(data.length() - 1, 1);
        file.close();
    }
    else
    {
        qDebug()<<"Error while opening "<<filePath;
        return -1;
    }
    return 0;
}

/**
 * @brief CServiceMPL3115::eventLoop
 */
void CServiceMPL3115::eventLoop()
{
    if (!m_enabled)
        return;

    bool ret;

    /**
      * Temperature
      */
    QByteArray rawTemp, scaleTemp;

    if ( (ret = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp_raw", rawTemp)) !=0 )
    {
        qDebug()<<"Error with rawTemp";
    }

    if ( (ret = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp_scale", scaleTemp)) !=0 )
    {
        qDebug()<<"Error with scaleTemp";
    }

    m_temperature = rawTemp.toInt() * scaleTemp.toDouble();

    /**
      * Pressure
      */
    QByteArray rawPressure, scalePressure;

    if ( (ret = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_pressure_raw", rawPressure)) !=0 )
    {
        qDebug()<<"Error with rawPressure";
    }
    if ( (ret = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_pressure_scale", scalePressure)) !=0 )
    {
        qDebug()<<"Error with scalePressure";
    }

    m_pressure = rawPressure.toInt() * scalePressure.toDouble();
}
