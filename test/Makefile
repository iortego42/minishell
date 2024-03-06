MAKEFILE_DIR=.
PROJECT_DIR=..
TEST_DIR=.

CPPUTEST_HOME=cpputest
# SRC_DIRS=$(TEST_DIR)/src
INCLUDE_DIRS=$(PROJECT_DIR)/include
INCLUDE_DIRS+=$(PROJECT_DIR)/libft/include
INCLUDE_DIRS+=$(PROJECT_DIR)/libstrings/include
INCLUDE_DIRS+=$(CPPUTEST_HOME)/include

CPPUTEST_OBJS_DIR=$(TEST_DIR)/objs
CPPUTEST_LIB_DIR=$(TEST_DIR)/lib


CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

TEST_SRC_DIRS=$(TEST_DIR)

lexer: 
	# CREACION DE LAS VARIABLES 
	$(eval COMPONENT_NAME=lexer)
	$(eval SRC_FILES=../src/parser/lexer.c)
	@echo "Testing Lexer. $(COMPONENT_NAME)"
	$(MAKE) run COMPONENT_NAME=lexer SRC_FILES=../src/parser/lexer.c
	
init:
	cd cpputest
	./autogen.sh
	./configure
	make all
	


run: start $(TEST_TARGET) 
	$(RUN_TEST_TARGET)

cleantest:
	rm -rf objs lib .a src

.PHONY: run lexer cleantest init

include $(CPPUTEST_HOME)/build/MakefileWorker.mk