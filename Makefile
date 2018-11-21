SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
SRC_FILES = $(shell find src -name '*.cc' | sort -k 1nr | cut -f2-)
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cc=.o))
DEP_FILES = $(patsubst $(SRC_DIR)/%,$(DEP_DIR)/%,$(SRC_FILES:.cc=.d))
DEP_DIRS = $(sort $(dir $(DEP_FILES)))

CXX = g++
DEP_LOC = $(patsubst $(OBJ_DIR)/%,$(DEP_DIR)/%,$*.d)
DEPFLAGS = -MT $(DEP_LOC) -MMD -MP -MF $(DEP_LOC)
WFLAGS = -Wall -Werror -g
CPPFLAGS = -std=c++14 $(WFLAGS) $(DEPFLAGS) -I $(SRC_DIR)
CXXFLAGS = -std=c++14 $(WFLAGS) -lncurses
EXEC = vm



objects: ${DEP_DIRS} ${OBJ_FILES} ${OBJ_FILES}

$(EXEC): ${OBJ_FILES}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJ_FILES} 

$(OBJ_FILES): $(SRC_FILES)
	mkdir -p $(dir $@)
	${CXX} $(CPPFLAGS) -c -o $@ $< 

-include ${DEP_FILES}

.PHONY: $(DEP_DIRS)

$(DEP_DIRS):
	mkdir -p $@

.PHONY: clean

clean:
	rm -f ${OBJ_FILES} ${DEP_FILES} ${EXEC}
