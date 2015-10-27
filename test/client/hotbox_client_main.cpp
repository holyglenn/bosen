#include "client/hb_client.hpp"
#include "facility/test_facility.hpp"
#include <glog/logging.h>
#include <gflags/gflags.h>

int main(int argc, char *argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  hotbox::HBClient hb_client;
  hotbox::SessionOptions session_options;
  session_options.db_name = "test_db";
  session_options.session_id = "test_session";
  session_options.transform_config_path = hotbox::GetTestDir() +
    "/resource/test_transform1.conf";
  session_options.output_store_type = hotbox::OutputStoreType::DENSE;
  hotbox::Session session = hb_client.CreateSession(session_options);
  CHECK(session.GetStatus().IsOk());
  hotbox::OSchema o_schema = session.GetOSchema();
  LOG(INFO) << "OSchema: " << o_schema.ToString();
  auto p = o_schema.GetName(4);
  LOG(INFO) << "o_schema(4): family: " << p.first << " feature_name: "
                           << p.second;
  int i = 0;
  for (hotbox::DataIterator it = session.NewDataIterator(0, 5); it.HasNext();
      it.Next()) {
    hotbox::FlexiDatum datum = it.GetDatum();
    LOG(INFO) << datum.ToString();
    i++;
  }
  LOG(INFO) << "Read " << i << " data";
  return 0;
};
