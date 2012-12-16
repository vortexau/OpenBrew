AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = openbrew
openbrew_SOURCES =              lib/pugixml-1.2/src/pugixml.cpp \
				src/batch/Batch.cpp       \
                                src/pump/BrownPump.cpp    \
                                src/pump/MarchPump.cpp    \
                                src/pump/Pump.cpp             \
                                src/runBatch/runBatch.cpp \
                                src/sensor/Sensor.cpp     \
                                src/step/hltAutoFill.cpp  \
                                src/step/hltBoil.cpp      \
				src/step/Step.cpp	\
                                src/vessel/Hlt.cpp                \
                                src/vessel/Mlt.cpp                \
                                src/vessel/Kettle.cpp     \
				src/vessel/Vessel.cpp \
                                src/main.cpp


dist_noinst_SCRIPTS = autogen.sh				
