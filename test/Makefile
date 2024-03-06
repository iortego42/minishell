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

TEST_SRC_DIRS=$(TEST_DIR)/test_srcs


#
# --- LIBSTRINGS ---
#
LSTRINGSPATH = $(PROJECT_DIR)/libstrings
LSTRINGSNAME = strings
LSTRINGS = $(LSTRINGSPATH)/lib$(LSTRINGSNAME).a

$(LSTRINGS):
	make -C $(LSTRINGSPATH)

#
# --- LIBFT ---
#
LFTPATH = $(PROJECT_DIR)/libft
LFTNAME = ft
LFT = $(LFTPATH)/lib$(LFTNAME).a
$(LFT):
	make -C $(LFTPATH)

CPPUTEST_CFLAGS+=-I $(LSTRINGSPATH)/include
CPPUTEST_LDFLAGS+=-L $(LSTRINGSPATH) -l$(LSTRINGSNAME)

lexer: $(LSTRINGS)
	# CREACION DE LAS VARIABLES 
	@echo "Testing Lexer."
	$(MAKE) run COMPONENT_NAME=lexer SRC_FILES=../src/parser/lexer.c CPPUTEST_CFLAGS="$(CPPUTEST_CFLAGS)" CPPUTEST_LDFLAGS="$(CPPUTEST_LDFLAGS)"
	
init:
	cd cpputest
	./autogen.sh
	./configure
	make all
	


run: start $(TEST_TARGET) 
	$(RUN_TEST_TARGET) -c

cleantest:
	rm -rf objs lib .a src

.PHONY: run lexer cleantest init libstrings

include $(CPPUTEST_HOME)/build/MakefileWorker.mk