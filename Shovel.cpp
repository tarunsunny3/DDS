// #include <fstream>
// #include <dds/DCPS/Service_Participant.h>
// #include <dds/DCPS/transport/framework/TransportRegistry.h>
// #include <dds/DCPS/transport/framework/TransportConfig.h>
// #include <ace/OS_NS_sys_time.h>
// #include "TonnageTypeSupportImpl.h"
//New header files
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>
#include "dds/DCPS/StaticIncludes.h"
#ifdef ACE_AS_STATIC_LIBS
#include <dds/DCPS/RTPS/RtpsDiscovery.h>
#include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif
#include "TonnageTypeSupportImpl.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ace/OS_NS_time.h>
class TonnageListener : public DDS::DataReaderListener {
public:
  virtual void on_data_available(DDS::DataReader_ptr reader) {
    Mining::TonnageDataReader_var reader_i =
      Mining::TonnageDataReader::_narrow(reader);

    Mining::Tonnage tonnage;
    DDS::SampleInfo info;

    DDS::ReturnCode_t error = reader_i->take_next_sample(tonnage, info);
    if (error == DDS::RETCODE_OK && info.valid_data) {
      long long latency = ACE_OS::gettimeofday().msec() - tonnage.timeStamp;  // Calculate latency

      std::ofstream outfile;
      outfile.open("latency.csv", std::ios_base::app);  // Append to the file
      outfile << latency << "\n";  // Write latency to file
      outfile.close();

      if (tonnage.seqNumber != last_sequence + 1) {  // Check sequence number
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                   ACE_TEXT(" out-of-sequence message received: expected %d but got %d\n"),
                   last_sequence + 1, tonnage.seqNumber));
      }

      last_sequence = tonnage.seqNumber;
    } else {
      ACE_ERROR((LM_ERROR,
                 ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                 ACE_TEXT(" take_next_sample returned %d!\n"), error));
    }
  }

private:
  long last_sequence = -1;
};

int ACE_TMAIN(int argc, ACE_TCHAR* argv[]) {
  try {
    // Initialize DomainParticipantFactory
    DDS::DomainParticipantFactory_var dpf =
      TheParticipantFactoryWithArgs(argc, argv);

    // Create DomainParticipant
    DDS::DomainParticipant_var participant =
      dpf->create_participant(42,
                              PARTICIPANT_QOS_DEFAULT,
                              0,
                              OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    // Register TypeSupport
    Mining::TonnageTypeSupport_var ts = new Mining::TonnageTypeSupportImpl;

    if (ts->register_type(participant, "") != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("Failed to register the TonnageTypeSupport.")),
                       1);
    }

    // Create Topic
    DDS::Topic_var topic =
      participant->create_topic("Mining Tonnage",
                                ts->get_type_name(),
                                TOPIC_QOS_DEFAULT,
                                0,
                                OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    // Create Subscriber
    DDS::Subscriber_var sub =
      participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,
                                     0,
                                     OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    // Create DataReader
    DDS::DataReaderListener_var listener(new TonnageListener);
    DDS::DataReader_var dr =
      sub->create_datareader(topic,
                             DATAREADER_QOS_DEFAULT,
                             listener,
                             OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    // Wait for samples to arrive
    ACE_OS::sleep(ACE_Time_Value(60, 0));  // Sleep for 60 seconds

    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);
    TheServiceParticipant->shutdown();
  } catch (const CORBA::Exception& e) {
    e._tao_print_exception("Exception caught in main():");
    return 1;
  }

  return 0;
}
