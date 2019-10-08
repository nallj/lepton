# Makefile for the Task Graph For Free (TGFF) to Drachma utility application known as Lepton:
# A program for utilizing task graphs produced from TGFF as inputs for creating pseudo-random
# trace files for use with Drachma.

# Written by James B. Nall
# Copyright (C) 2015-2019, All Rights Reserved

CXX = g++
CXXFLAGS = -std=c++11 -o
OBJ = applicationTrace.o availableModule.o fileReader.o graph.o lepton.o graphNode.o mapper.o moduleIterationActions.o parameterParser.o parameters.o

# Ignore the rest of this for now.
ifeq ("true","false")

all: $(OBJ) -o lepton

dev: $(OBJ) -g -o lepton

clean:
	rm -f *.o
#	rm -f src/*.o src/parameters/*.o


applicationTrace.o: src/core/applicationTrace.h src/core/availableModule.h
	$(CXX) $@ $^

availableModule.o: src/core/availableModule.h src/graphNode.h
	$(CXX) $@ $^

fileReader.o: src/fileReader.h
	$(CXX) $@ $<
# -lboost_regex

graph.o: src/graph.h src/graphNode.h
	$(CXX) $@ $^

graphMapper.o: src/core/applicationTrace.h src/core/availableModule.h src/fileReader.h src/graph.h src/graphNode.h src/core/reconfigurableRegions.h src/parameters/parameterParser.h src/parameters/parameters.h src/mapper.h
	$(CXX) $@ $^

# applicationTrace
graphNode.o: src/graphNode.h
	$(CXX) $@ $<

mapper.o: src/core/applicationTrace.h src/core/availableModule.h src/fileReader.h src/graph.h src/moduleIterationActions.h src/parameters/parameters.h
	$(CXX) $@ $^

moduleIterationActions.o: src/core/availableModule.h src/graphNode.h src/moduleIterationActions.h
	$(CXX) $@ $^

parameterParser.o: src/parameters/parameterParser.h
	$(CXX) $@ $<

parameters.o: src/parameters/parameters.h
	$(CXX) $@ $<


lepton: src/main.cpp $(OBJ)
	$(CXX) -c $@ $^
#	cd src; $(CXX) -c -o $@ $^

endif

# all: src/main.cpp src/core/applicationTrace.h src/core/applicationTrace.cpp \
#			 src/core/availableModule.h src/core/availableModule.cpp src/helpers/debugHelper.h \
# 		 src/helpers/debugHelper.cpp src/files/fileReader.h src/files/fileReader.cpp \
# 		 src/files/fileWriter.h src/files/fileWriter.cpp src/files/drachmaAppFileReader.h \
# 		 src/files/drachmaAppFileReader.cpp src/files/leptonSpecFileReader.cpp \
# 		 src/files/leptonSpecFileReader.h src/graph/graph.h src/graph/graph.cpp src/graph/graphHandler.h \
# 		 src/graph/graphHandler.cpp src/graph/graphMapper.h src/graph/graphMapper.cpp \
# 		 src/graph/graphNode.h src/graph/graphNode.cpp src/helpers/moduleHelper.h \
# 		 src/helpers/moduleHelper.cpp src/helpers/moduleIterationActions.h \
# 		 src/helpers/moduleIterationActions.cpp src/core/reconfigurableRegions.h \
# 		 src/core/reconfigurableRegions.cpp src/helpers/nodeHelper.h src/helpers/nodeHelper.cpp \
# 		 src/parameters/parameterBuilder.h src/parameters/parameterBuilder.cpp \
# 		 src/parameters/parameterParser.h src/parameters/parameterParser.cpp src/parameters/ipParam.h \
# 		 src/parameters/srParam.h src/parameters/srParam.cpp src/parameters/rrParam.h \
#      src/parameters/rrParam.cpp

all: src/main.cpp src/core/applicationTrace.cpp src/core/availableModule.cpp \
     src/helpers/debugHelper.cpp src/files/fileReader.cpp src/files/fileWriter.cpp \
		 src/files/drachmaAppFileReader.cpp src/files/leptonSpecFileReader.cpp \
		 src/graph/graphHandler.cpp src/graph/graphMapper.cpp \
		 src/helpers/moduleHelper.cpp \
		 src/helpers/moduleIterationActions.cpp \
		 src/core/reconfigurableRegions.cpp src/helpers/nodeHelper.cpp \
		 src/parameters/parameterBuilder.cpp \
		 src/parameters/parameterParser.cpp src/parameters/srParam.cpp src/parameters/rrParam.cpp

	# cd src && \
	# $(CXX) -g $(CXXFLAGS) ../lepton main.cpp core/applicationTrace.h core/applicationTrace.cpp \
	# core/availableModule.h core/availableModule.cpp helpers/debugHelper.h \
	# helpers/debugHelper.cpp files/fileReader.h files/fileReader.cpp  files/fileWriter.h \
	# files/fileWriter.cpp files/drachmaAppFileReader.h files/drachmaAppFileReader.cpp \
	# files/leptonSpecFileReader.cpp files/leptonSpecFileReader.h graph/graph.h graph/graph.cpp \
	# graph/graphHandler.h graph/graphHandler.cpp graph/graphMapper.h graph/graphMapper.cpp \
	# graph/graphNode.h graph/graphNode.cpp helpers/moduleHelper.h helpers/moduleHelper.cpp \
	# helpers/moduleIterationActions.h helpers/moduleIterationActions.cpp core/reconfigurableRegions.h \
	# core/reconfigurableRegions.cpp	helpers/nodeHelper.h helpers/nodeHelper.cpp \
	# parameters/parameterBuilder.h parameters/parameterBuilder.cpp parameters/parameterParser.h \
	# parameters/parameterParser.cpp parameters/ipParam.h parameters/srParam.h parameters/srParam.cpp \
	# parameters/rrParam.h parameters/rrParam.cpp
	# -lboost_regex
	cd src && \
	$(CXX) -g $(CXXFLAGS) ../lepton main.cpp core/applicationTrace.cpp core/availableModule.cpp \
	helpers/debugHelper.cpp files/fileReader.cpp files/fileWriter.cpp files/drachmaAppFileReader.cpp \
	files/leptonSpecFileReader.cpp graph/graph.cpp graph/graphHandler.cpp graph/graphMapper.cpp \
	graph/graphNode.cpp helpers/moduleHelper.cpp helpers/moduleIterationActions.cpp \
	core/reconfigurableRegions.cpp helpers/nodeHelper.cpp parameters/parameterBuilder.cpp \
	parameters/parameterParser.cpp parameters/srParam.cpp parameters/rrParam.cpp \
	-lboost_regex
	#g++ -std=c++11 -o lepton src/main.cpp src/applicationTrace.h src/core/availableModule.h src/debugHelper.h src/debugHelper.cpp src/fileReader.h src/fileReader.cpp  src/graph/graph.h src/graph/graphHandler.h src/graph/graphHandler.cpp src/graph/graphMapper.h src/graph/graphMapper.cpp src/graph/graphNode.h src/graph/moduleHelper.h src/graph/moduleHelper.cpp src/graph/moduleIterationActions.h src/graph/moduleIterationActions.cpp src/parameters/parameterBuilder.h src/parameters/parameterBuilder.cpp src/parameters/parameterParser.h src/parameters/parameterParser.cpp src/parameters/parameters.h

clean:
	rm -f *.o lepton
