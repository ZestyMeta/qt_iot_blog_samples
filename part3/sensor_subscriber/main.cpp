#include "sensor.hpp"
#include "dds/sub/Subscriber.hpp"
#include "dds/sub/DataReader.hpp"
#include "dds/sub/DataReaderListener.hpp"

#include <QCoreApplication>
#include <QDebug>

QDebug operator<<(QDebug d, const sensor_information &sensor)
{
    std::ostringstream stream;
    stream << sensor;

    d << "Sensor( " << QString::fromStdString(stream.str()) << ")";
    return d;
}

class ReaderListener : public dds::sub::DataReaderListener<sensor_information> {
  public:
    ReaderListener() : dds::sub::DataReaderListener<sensor_information>()
    {
        qDebug() << Q_FUNC_INFO;
    }
    void on_requested_deadline_missed(dds::sub::DataReader<sensor_information> &, const dds::core::status::RequestedDeadlineMissedStatus &) override
    {
        qDebug() << Q_FUNC_INFO;
    }

    void on_requested_incompatible_qos(dds::sub::DataReader<sensor_information> &, const dds::core::status::RequestedIncompatibleQosStatus &) override
    {
        qDebug() << Q_FUNC_INFO;
    }

    void on_sample_rejected(dds::sub::DataReader<sensor_information> &, const dds::core::status::SampleRejectedStatus &) override
    {
        qDebug() << Q_FUNC_INFO;
    }

    void on_liveliness_changed(dds::sub::DataReader<sensor_information> &, const dds::core::status::LivelinessChangedStatus &status) override
    {
        // Liveliness only reports availability, not the initial state of a sensor
        // Follow up changes are reported to on_data_available
        qDebug() << Q_FUNC_INFO << status.alive_count();
    }

    void on_sample_lost(dds::sub::DataReader<sensor_information> &, const dds::core::status::SampleLostStatus &) override
    {
        qDebug() << Q_FUNC_INFO;
    }

    void on_subscription_matched(dds::sub::DataReader<sensor_information> &, const dds::core::status::SubscriptionMatchedStatus &) override
    {
        qDebug() << Q_FUNC_INFO;
    }

    void on_data_available(dds::sub::DataReader<sensor_information> &) override;
};

void ReaderListener::on_data_available(dds::sub::DataReader<sensor_information> &reader)
{
    for(sensor_information sample : reader.take())
    {
        qDebug() << sample;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const DDS_DomainId_t domainId = 0;
    dds::domain::DomainParticipant participant(domainId);
    if (dds::core::null == participant) {
        qDebug() << "Could not create participant.";
        return -1;
    }

    dds::sub::Subscriber subscriber(participant);
    if (dds::core::null == subscriber) {
        qDebug() << "Could not create subscriber.";
        return -2;
    }

    std::string topic_name = "Sensor Information";
    dds::topic::Topic<sensor_information> topic(participant, topic_name);
    if (dds::core::null == topic) {
        qDebug() << "Could not create topic.";
        return -3;
    }

    ReaderListener *listener = new ReaderListener();
    if (!listener) {
        qDebug() << "Could not create listener.";
        return -5;
    }

    dds::sub::DataReader<sensor_information> reader(subscriber, topic, subscriber.default_datareader_qos(), listener);
    if (dds::core::null == reader) {
        qDebug() << "Could not create reader.";
        return -6;
    }

    qDebug() << "Subscribed, now waiting...";

    return a.exec();
}
