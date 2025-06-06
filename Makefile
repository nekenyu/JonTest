#
# Top Level Makefile
#

# Default target
all:

# Subdirectories to be made and dependencies
#

SUBDIRS+= src
SUBDIRS+= examples
SUBDIRS+= test
examples: src
test: src

# Targets supported
#
all clean cleaner cleanest: $(SUBDIRS)
all: TARGET=all
clean: TARGET=clean
cleaner: TARGET=cleaner
cleanest: TARGET=cleanest

# Recursive make in the subdirectories
#
.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	@echo Entering directory \`$@\'
	+make -C $@ $(TARGET)
	@echo Leaving directory \`$@\'


# Other tasks
#

.PHONY: docs
all: docs
docs:
	doxygen Doxyfile

.PHONY: run-examples
run-examples: all
	build/examples/SimpleTest.exe
	build/examples/TestCaseOrder.exe 

.PHONY: run-test
run-test: all
	build/test/unit-test.exe

.PHONY: world
world: run-test run-examples all
