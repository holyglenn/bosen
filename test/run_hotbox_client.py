#!/usr/bin/env python

import sys, os, time
from os.path import dirname
from os.path import join

project_dir = dirname(os.path.realpath(__file__))
#os.system('mkdir -p %s' % db_testbed)
prog = join(project_dir, "build", "hotbox_client_main")

env_params = (
  "GLOG_logtostderr=true "
  "GLOG_v=-1 "
  "GLOG_minloglevel=0 "
  )

cmd = env_params + prog
#cmd += "".join([" --%s=%s" % (k,v) for k,v in params.items()])
print cmd
os.system(cmd)
