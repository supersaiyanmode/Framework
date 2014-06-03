
# Define executable name
BIN = bin/libcmsclient.so

# Define source files
SRCS = ./src/CMSClient.cpp ./src/CMSServerConnection.cpp ./src/QueueReceiver.cpp ./src/QueueSender.cpp ./src/TopicPublisher.cpp ./src/TopicSubscriber.cpp

# Define header file paths
INCPATH = -I ./include -I ../Server/include -I ../../GenericServer/include -I ../../../Random/include \
		-I ../../../Thread/include -I ../../../Time/include

# Define the -L library path(s)
LDFLAGS = -L ../Server/bin -L ../../GenericServer/bin -L ../../../Random/bin -L ../../../Thread/bin \
		-L ../../../Time/bin

# Define the -l library name(s)
LIBS = -lcmsserver -ltcpserver -lrandomutil -lthreadingutil -ltimeutil

# Define Compile Flags
COMPILEFLAGS = -Wall -pedantic -fPIC 

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

