CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD g
EXEC = vm
OBJECTS = application.o
DEPENDS = ${OBJECTS:.o=.d}

#${EXEC}: ${OBJECTS}
#	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${DEPENDS} #${EXEC} 
