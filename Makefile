SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = obj
#don't know how to create them in different dir
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cc)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.cc,$(DEP_DIR)/%.d,$(SRC_FILES))

CXX = g++
CPPFLAGS = -std=c++14 -Wall -MMD -g -I $(SRC_DIR)
CXXFLAGS = -std=c++14 -Wall -g
EXEC = vm



objects: ${OBJ_FILES}

${EXEC}: ${OBJ_FILES}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJ_FILES} -lncurses

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	${CXX} $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< -lncurses


-include ${DEP_FILES}

.PHONY: clean

clean:
	rm -f ${OBJ_FILES} ${DEP_FILES} #${EXEC} 


