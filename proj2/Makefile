#
# Makefile for gerp
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g
dot_os = gerp.o Parcer.o GerpSimulation.o LinesOfCode.o stringProcessing.o \
		   testWordHashTemplate.o testLinesOfCode.o

all: testWordHashTemplate gerp testLinesOfCode

gerp: gerp.o Parcer.o GerpSimulation.o LinesOfCode.o stringProcessing.o \
	  DirNode.o FSTree.o
	${CXX} ${CXXFLAGS} -o gerp gerp.o Parcer.o GerpSimulation.o LinesOfCode.o \
	 					  stringProcessing.o DirNode.o FSTree.o

testWordHashTemplate: testWordHashTemplate.o 
	${CXX} ${CXXFLAGS} -o testWordHashTemplate testWordHashTemplate.o

testLinesOfCode: testLinesOfCode.o LinesOfCode.o Parcer.o FSTree.o DirNode.o \
				 stringProcessing.o
	${CXX} ${CXXFLAGS} -o testLinesOfCode testLinesOfCode.o LinesOfCode.o \
					      Parcer.o FSTree.o DirNode.o stringProcessing.o

gerp.o: gerp.cpp 
Parcer.o: Parcer.cpp Parcer.h WordHashTemplate.h stringProcessing.h
GerpSimulation.o: GerpSimulation.cpp GerpSimulation.h LinesOfCode.h
LinesOfCode.o: LinesOfCode.cpp LinesOfCode.h Parcer.h FSTree.h DirNode.h
stringProcessing.o: stringProcessing.cpp stringProcessing.h
testWordHashTemplate.o: WordHashTemplate.h
testLinesOfCode.o: LinesOfCode.h

clean:
	rm -rf all dot_os *.dSYM

provide:
	provide comp15 proj2part3 DirNode.o DirNode.h FSTree.o FSTree.h gerp.cpp \
			GerpSimulation.cpp GerpSimulation.h LinesOfCode.cpp LinesOfCode.h \
			Makefile Parcer.cpp Parcer.h stringProcessing.cpp README \
			stringProcessing.h testLinesOfCode.cpp testWordHashTemplate.cpp \
			WordHashTemplate.h 


