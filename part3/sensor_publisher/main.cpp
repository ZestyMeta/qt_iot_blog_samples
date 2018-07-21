#include "sensor.hpp"
#include <dds/pub/DataWriter.hpp>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const DDS_DomainId_t domainId = 0;
    dds::domain::DomainParticipant participant(domainId);
    if (dds::core::null == participant) {
        qDebug() << "Could not create participant.";
        return -1;
    }

    dds::pub::Publisher publisher(participant);
    if (dds::core::null == publisher) {
        qDebug() << "Could not create publisher.";
        return -2;
    }

    std::string topic_name = "Sensor Information";
    dds::topic::Topic<sensor_information> topic(participant, topic_name);
    if (dds::core::null == topic) {
        qDebug() << "Could not create topic.";
        return -3;
    }

    dds::pub::DataWriter<sensor_information> writer(publisher, topic);
    if (dds::core::null == writer) {
        qDebug() << "Could not create writer.";
        return -4;
    }

    // Create real data
    sensor_information sensorInformation;
    sensorInformation.ID("Foobidoo");
    sensorInformation.ambientTemperature(12.);
    // As sensors have a unique ID, register each sensor to reuse data
    dds::core::InstanceHandle sensorHandle = writer.register_instance(sensorInformation);

    // Send data twice within a one second interval
    writer.write(sensorInformation, sensorHandle);

    dds::core::Duration send_period{1,0};
    rti::util::sleep(send_period);
    sensorInformation.ambientTemperature(14.);

    writer.write(sensorInformation, sensorHandle);

    qDebug() << "Publishing done.";

    return a.exec();
}
