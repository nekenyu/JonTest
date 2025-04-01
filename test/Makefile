#
# test Makefile
#

TOPDIR= ../

# Libraries
include $(TOPDIR)/Makefile.lib.incl
CXXFLAGS+= ${LIB_JON_TEST_FLAGS}
LIBS+= ${LIB_JON_TEST_LIBS}
LIB_DEP += ${LIB_JON_TEST_FILE}

#include $(TOPDIR)/Make/Makefile.googletest.incl
#CXXFLAGS+= ${LIB_GOOGLETEST_FLAGS}
#LIBS+= ${LIB_GOOGLETEST_MAIN_LIBS}
#LIBS+= ${LIB_GOOGLETEST_LIBS}

# Targets
MAKE_EXE=unit-test.exe
include $(TOPDIR)/Make/Makefile.incl
