FRAMEWORK_BASE = ../..
GENERIC_CLIENT = $(FRAMEWORK_BASE)/ClientServer/GenericClient

# Define executable name
BIN = build/libtcpserver.so

# Define source files
SRCS = ./src/BaseTCPServer.cpp \
		./src/RequestProcessors/ForkingRequestProcessor.cpp \
		./src/RequestProcessors/ThreadingRequestProcessor.cpp \
		./src/RequestProcessors/ThreadPoolRequestProcessor.cpp \
		./src/ServerSkeleton.cpp \
		./src/ThreadingTCPServer.cpp \
		./src/ThreadPoolTCPServer.cpp

# Define header file paths
INCPATH = -I include/ \
	 		-I $(FRAMEWORK_BASE)/Thread/include \
			-I $(FRAMEWORK_BASE)/Time/include \
			-I $(GENERIC_CLIENT)/include

# Define the -L library path(s)
LDFLAGS = -L $(FRAMEWORK_BASE)/Thread/build \
	 		-L $(FRAMEWORK_BASE)/Time/build \
			-L $(GENERIC_CLIENT)/build

# Define the -l library name(s)
LIBS = -ldl -lpthread -lthreadingutil -ltimeutil -lgenericclient

# Define Compile Flags
COMPILEFLAGS = -g -Wall -pedantic -fPIC

# Define Link Flags
LINKFLAGS = -g -shared -fPIC

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
	@mkdir -p build/
	@$(CXX) $(LINKFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@
	@cp -R include build/

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

