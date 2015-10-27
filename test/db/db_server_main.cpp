#include <glog/logging.h>
#include <gflags/gflags.h>
#include <iostream>

#include "db/db_server.hpp"
#include "db/proto/db.pb.h"
#include "facility/test_facility.hpp"
#include "io/filesys.hpp"

int main(int argc, char *argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  hotbox::DBServerConfig server_config;
  std::string db_test_bed_dir = hotbox::GetTestBedDir() + "/test_db_root";
  LOG(INFO) << "db_test_bed_dir: "  << db_test_bed_dir;
  server_config.set_db_dir(db_test_bed_dir);

  hotbox::DBServer db_server(server_config);
  LOG(INFO) << "DB Server initialized.";
  db_server.Start();

  return 0;
};
