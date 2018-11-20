SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = obj
#don't know how to create them in different dir
OBJ_DIRS = obj $(patsubst $(SRC_DIR)/%/,$(OBJ_DIR)/%/,$(wildcard $(SRC_DIR)/**/))
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cc)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.cc,$(DEP_DIR)/%.d,$(SRC_FILES))

CXX = g++
CPPFLAGS = -std=c++14 -Wall -MMD -g -I $(SRC_DIR)
CXXFLAGS = -std=c++14 -Wall -g -lncurses
EXEC = vm



objects: $(OBJ_DIRS) ${OBJ_FILES}

${EXEC}: ${OBJ_FILES}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJ_FILES} 

$(OBJ_DIRS): %:
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc 
	${CXX} $(CPPFLAGS) -c -o $@ $< 


-include ${DEP_FILES}

.PHONY: clean

clean:
	rm -rf ${OBJ_DIR} #${EXEC} 


