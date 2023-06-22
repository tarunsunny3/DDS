#include <fstream>
#include <random>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/transport/framework/TransportRegistry.h>
#include <dds/DCPS/transport/framework/TransportConfig.h>
#include <ace/OS_NS_sys_time.h>
#include "TonnageTypeSupportImpl.h"

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

    // Create Publisher
    DDS::Publisher_var pub =
      participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                    0,
                                    OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    // Create DataWriter
    DDS::DataWriter_var dw =
      pub->create_datawriter(topic,
                             DATAWRITER_QOS_DEFAULT,
                             0,
                             OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    Mining::TonnageDataWriter_var writer =
      Mining::TonnageDataWriter::_narrow(dw);

    // Write Tonnage samples
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 100.0);

    for (int i = 0; i < 6; ++i) {  // run for 1 minute (6 intervals of 10 seconds)
      Mining::Tonnage tonnage;
      tonnage.value = distribution(generator);  // Random tonnage value
      tonnage.timeStamp = ACE_OS::gettimeofday().msec();  // Current time in microseconds
      tonnage.seqNumber = i;  // Set sequence number

      DDS::ReturnCode_t error = writer->write(tonnage, DDS::HANDLE_NIL);
      if (error != DDS::RETCODE_OK) {
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                   ACE_TEXT(" write returned %d!\n"), error));
      }

      ACE_OS::sleep(ACE_Time_Value(10, 0));  // Sleep for 10 seconds
    }

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
