
# Define executable name
BIN = build/libgenericclient.so

# Define source files
SRCS = ./src/SocketIO/Connection.cpp \
		./src/SocketIO/Socket.cpp \
		./src/SocketIO/SocketException.cpp \
		./src/SocketIO/TCPClientSocket.cpp \
		./src/SocketIO/TCPServerSocket.cpp \
		./src/SocketIO/TCPSocket.cpp \
		./src/Structure/Block/BlockReader.cpp \
		./src/Structure/Block/BlockWriter.cpp \
		./src/Structure/Line/LineReader.cpp \
		./src/Structure/Line/LineWriter.cpp
		
TEST_SRCS = ./test/main.cpp

# Define header file paths
INCPATH = -I./include

# Define the -L library path(s)
LDFLAGS = 

# Define the -l library name(s)
LIBS = 

# Define Compile Flags
COMPILEFLAGS = -Wall -pedantic

# Define Link Flags
LINKFLAGS = -shared -fPIC

# Do not make any changes below!
OBJS      = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

CXX       = g++
DEP_FILE  = .depend

.PHONY = all clean distclean


# Main entry point
#
all: depend $(BIN)


# For linking object file(s) to produce the executable
#
$(BIN): $(OBJS) $(TEST_OBJS)
	@echo Linking $@
	@mkdir -p build/include
	@$(CXX) $(LINKFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@
	@cp -R include build/.

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

