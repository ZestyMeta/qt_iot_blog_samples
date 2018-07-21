#include "sensorinformation.h"

#include <QtCore/QDebug>
#include <QtCore/QUuid>

static const DDS_DomainId_t domainId = 0;

SensorInformation::SensorInformation(QObject *parent) :
    QObject(parent),
    m_participant(domainId),
    m_publisher(m_participant),
    m_topic(m_participant, "Sensor Information"),
    m_writer(m_publisher, m_topic)
{
    // Create real data
    m_id = QUuid::createUuid().toString().mid(1, 8);
    m_info.ID(m_id.toStdString());
}

void SensorInformation::sync()
{
    m_writer.write(m_info);
}

double SensorInformation::ambientTemperature() const
{
    return m_info.ambientTemperature();
}

double SensorInformation::objectTemperature() const
{
    return m_info.objectTemperature();
}

double SensorInformation::accelerometerX() const
{
    return m_info.accelerometerX();
}

double SensorInformation::accelerometerY() const
{
    return m_info.accelerometerY();
}

double SensorInformation::accelerometerZ() const
{
    return m_info.accelerometerZ();
}

double SensorInformation::altitude() const
{
    return m_info.altitude();
}

double SensorInformation::light() const
{
    return m_info.light();
}

double SensorInformation::humidity() const
{
    return m_info.humidity();
}

QString SensorInformation::identifier() const
{
    return m_id;
}

void SensorInformation::setAmbientTemperature(double ambientTemperature)
{
    if (qFuzzyCompare(m_info.ambientTemperature(), ambientTemperature))
        return;

    m_info.ambientTemperature(ambientTemperature);
    emit ambientTemperatureChanged(ambientTemperature);
    sync();
}

void SensorInformation::setObjectTemperature(double objectTemperature)
{
    if (qFuzzyCompare(m_info.objectTemperature(), objectTemperature))
        return;

    m_info.objectTemperature(objectTemperature);
    emit objectTemperatureChanged(objectTemperature);
    sync();
}

void SensorInformation::setAccelerometerX(double accelerometerX)
{
    if (qFuzzyCompare(m_info.accelerometerX(), accelerometerX))
        return;

    m_info.accelerometerX(accelerometerX);
    emit accelerometerXChanged(accelerometerX);
    sync();
}

void SensorInformation::setAccelerometerY(double accelerometerY)
{
    if (qFuzzyCompare(m_info.accelerometerY(), accelerometerY))
        return;

    m_info.accelerometerY(accelerometerY);
    emit accelerometerYChanged(accelerometerY);
    sync();
}

void SensorInformation::setAccelerometerZ(double accelerometerZ)
{
    if (qFuzzyCompare(m_info.accelerometerZ(), accelerometerZ))
        return;

    m_info.accelerometerZ(accelerometerZ);
    emit accelerometerZChanged(accelerometerZ);
    sync();
}

void SensorInformation::setAltitude(double altitude)
{
    if (qFuzzyCompare(m_info.altitude(), altitude))
        return;

    m_info.altitude(altitude);
    emit altitudeChanged(altitude);
    sync();
}

void SensorInformation::setLight(double light)
{
    if (qFuzzyCompare(m_info.light(), light))
        return;

    m_info.light(light);
    emit lightChanged(light);
    sync();
}

void SensorInformation::setHumidity(double humidity)
{
    if (qFuzzyCompare(m_info.humidity(), humidity))
        return;

    m_info.humidity(humidity);
    emit humidityChanged(humidity);
    sync();
}

void SensorInformation::setIdentifier(const QString &id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit identifierChanged(m_id);
    sync();
}
