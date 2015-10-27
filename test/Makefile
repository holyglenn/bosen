# Assuming this Makefile lives in project root directory
PROJECT := $(shell readlink $(dir $(lastword $(MAKEFILE_LIST))) -f)
PETUUM_ROOT = $(PROJECT)/../

include $(PETUUM_ROOT)/defns.mk



# Requires PROJECT to be defined as repo root dir

ifndef JAVA_HOME
  JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64
endif
ifndef LIBJVM
  LIBJVM=$(JAVA_HOME)/jre/lib/amd64/server
endif

#BUILD := $(PROJECT)/build
BUILD :=build
NEED_MKDIR = $(BUILD)

all: path test

path: $(NEED_MKDIR)

$(NEED_MKDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD)
	rm -rf db_testbed

.PHONY: all path clean

CXX = g++
CXXFLAGS += -O2 \
           -std=c++11 \
           -Wall \
					 -Wno-sign-compare \
           -fno-builtin-malloc \
           -fno-builtin-calloc \
           -fno-builtin-realloc \
           -fno-builtin-free \
           -fno-omit-frame-pointer \
					 -DDMLC_USE_GLOG=1

INCFLAGS =  -I$(PETUUM_THIRD_PARTY_INCLUDE)
INCFLAGS += -I$(PETUUM_THIRD_PARTY_INCLUDE)/hotbox
INCFLAGS += -I$(PETUUM_THIRD_PARTY_INCLUDE)/hotbox/build # include generated *pb.h
INCFLAGS += -I$(JAVA_HOME)/include # include java for HDFS/DMLC access
INCFLAGS += $(HDFS_INCFLAGS)

LDFLAGS = -Wl,-rpath,$(PETUUM_THIRD_PARTY_LIB) \
		  -Wl,-rpath=$(LIBJVM) \
          -L$(PETUUM_THIRD_PARTY_LIB) \
          -L$(LIBJVM) -ljvm \
          -lpthread -lrt -lnsl \
          -lzmq \
          -lglog \
          -lgflags \
          -ltcmalloc \
			-lprotobuf \
			-D_GLIBCXX_USE_NANOSLEEP \
			-lpthread \
			-lyaml-cpp \
			-lsnappy \
          -ldmlc \
          -lhdfs \
          -lrocksdb \
          -lhotbox \

HB_SRC = $(shell find src -type f -name "*.cpp")
HB_PROTO = $(shell find src -type f -name "*.proto")
HB_HEADERS = $(shell find src -type f -name "*.hpp")

TEST_DIR = $(PROJECT)/$(BUILD)
TEST_INCFLAGS = -I$(PROJECT)

HB_LIB = 
#$(PETUUM_THIRD_PARTY_LIB)/libhotbox.a


#$(TEST_DIR)/%: $(PROJECT)/%.cpp $(HB_LIB) /facility/test_facility.hpp
#	mkdir -p $(@D)
#	LD_LIBRARY_PATH=$(PETUUM_THIRD_PARTY_LIB) \
#	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TEST_INCFLAGS) \
#		$< -lgtest $(HB_LIB) $(LDFLAGS) -o $@

db_server_main: $(PROJECT)/db/db_server_main.cpp $(HB_LIB) \
	facility/test_facility.hpp
	mkdir -p $(@D)
	LD_LIBRARY_PATH=$(PETUUM_THIRD_PARTY_LIB) \
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TEST_INCFLAGS) $< \
	 -o $(TEST_DIR)/db_server_main \
		 -lgtest $(HB_LIB) $(LDFLAGS)

hotbox_client_main: $(PROJECT)/client/hotbox_client_main.cpp $(HB_LIB) \
	facility/test_facility.hpp
	mkdir -p $(@D)
	LD_LIBRARY_PATH=$(PETUUM_THIRD_PARTY_LIB) \
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TEST_INCFLAGS) $< \
		 -o $(TEST_DIR)/hotbox_client_main \
		 -lgtest $(HB_LIB) $(LDFLAGS)
		

test: db_server_main hotbox_client_main
