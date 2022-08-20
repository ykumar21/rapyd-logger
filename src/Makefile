OBJS = rapyd.o logger.o message.o process.o

CXX = clang++
CXX_STANDARD = c++20
CXXFLAGS = -std=${CXX_STANDARD} -g -Wc++11-extensions 

output: ${OBJS} 
	${CXX} ${CXXFLAGS} ${OBJS} -o output

rapyd.o: rapyd/rapyd.cpp rapyd/Message.cpp rapyd/Logger.cpp
	${CXX} ${CXXFLAGS} -c rapyd/rapyd.cpp rapyd/Message.cpp rapyd/Logger.cpp 

logger.o: rapyd/Logger.cpp rapyd/Message.cpp
	${CXX} ${CXXFLAGS} -c rapyd/Logger.cpp rapyd/Message.cpp 

message.o: rapyd/Message.cpp
	${CXX} ${CXXFLAGS} -c rapyd/Message.cpp 

process.o: rapyd/Process.cpp
	${CXX} ${CXXFLAGS} -c rapyd/Process.cpp

clean: 
	rm -f *.o output 


run:
	rm -f tmp/pipe/*; ./output
