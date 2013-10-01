
# Define executable name
BIN = bin/libtcpserver.so

# Define source files
SRCS = ./src/BaseTCPServer.cpp ./src/IO/InputOutputCapable.cpp ./src/IO/main.cpp ./src/IO/SocketIO/Connection.cpp ./src/IO/SocketIO/Socket.cpp ./src/IO/SocketIO/SocketException.cpp ./src/IO/SocketIO/TCPClientSocket.cpp ./src/IO/SocketIO/TCPServerSocket.cpp ./src/IO/SocketIO/TCPSocket.cpp ./src/IO/Structure/Block/BlockReader.cpp ./src/IO/Structure/Block/BlockWriter.cpp ./src/IO/Structure/Line/LineReader.cpp ./src/IO/Structure/Line/LineWriter.cpp ./src/Plugin.cpp ./src/RequestProcessors/ForkingRequestProcessor.cpp ./src/RequestProcessors/ThreadingRequestProcessor.cpp ./src/RequestProcessors/ThreadPoolRequestProcessor.cpp ./src/ServerSkeleton.cpp ./src/Thread/Condition.cpp ./src/Thread/Mutex.cpp ./src/Thread/ReadWriteLock.cpp ./src/Thread/test/prodcons.cpp ./src/Thread/test/ThreadPoolTest.cpp ./src/Thread/test/ThreadTest.cpp ./src/Thread/Thread.cpp ./src/Thread/ThreadLogger.cpp ./src/Thread/ThreadPool.cpp ./src/ThreadingTCPServer.cpp ./src/ThreadPoolTCPServer.cpp ./src/Time/Time.cpp

# Define header file paths
INCPATH = -I include/

# Define the -L library path(s)
LDFLAGS = 

# Define the -l library name(s)
LIBS = -ldl -lpthread

# Define Compile Flags
COMPILEFLAGS = -Wall -pedantic -shared -fPIC

# Define Link Flags
LINKFLAGS = -shared -fPIC

# Do not make any changes below!
OBJS      = $(SRCS:.cpp=.o)
CXX       = g++
DEP_FILE  = .depend

.PHONY = all clean distclean


# Main entry point
#
all: depend $(BIN)


# For linking object file(s) to produce the executable
#
$(BIN): $(OBJS)
	@echo Linking $@
	$(shell mkdir -p $(shell dirname $(BIN)))
	@$(CXX) $(LINKFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@


# For compiling source file(s)
#
.cpp.o:
	@echo Compiling $<
	@$(CXX) -c $(COMPILEFLAGS) $(INCPATH) $< -o $(<:.cpp=.o)


# For cleaning up the project
#
clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(BIN)
	$(RM) $(DEP_FILE)


# For determining source file dependencies
#
depend: $(DEP_FILE)
	@echo "Dependencies generated."
	
$(DEP_FILE):
	@echo Generating dependencies in $@
	@-$(CXX) -E -MM $(COMPILEFLAGS) $(INCPATH) $(SRCS) >> $(DEP_FILE)

ifeq (,$(findstring clean,$(MAKECMDGOALS)))
ifeq (,$(findstring distclean,$(MAKECMDGOALS)))
-include $(DEP_FILE)
endif
endif

