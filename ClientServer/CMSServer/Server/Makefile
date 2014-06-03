
# Define executable name
BIN = bin/libcmsserver.so

# Define source files
SRCS = ./src/CMSServer.cpp ./src/Core/BridgeProcessor.cpp ./src/Core/ClientEndPoint.cpp ./src/Core/MessageProcessor.cpp ./src/Protocol/CMSDestination/CMSDestGroup.cpp ./src/Protocol/CMSDestination/CMSDestination.cpp ./src/Protocol/CMSMessage/GenericCMSMessage.cpp ./src/Protocol/CMSMessage/Header/CMSHeaderSet.cpp ./src/Protocol/Exception/ProtocolException.cpp

# Define header file paths
INCPATH = -I../../GenericServer/include -I../../../ConfigurationFileParser/include \
			-I../../../StringUtils/include -Iinclude/ -I ../../../Thread/include -I ../../../Time/include \
			-I ../../../Random/include

# Define the -L library path(s)
LDFLAGS = -L../../../ConfigurationFileParser/bin -L../../../StringUtils/bin -L ../../GenericServer/bin \
			-L ../../../Thread/bin -L ../../../Time/bin -L ../../../Random/bin

# Define the -l library name(s)
LIBS = -lconfigparser -lstringutils -ltcpserver -lthreadingutil -ltimeutil -lrandomutil

# Define Compile Flags
COMPILEFLAGS = -Wall -pedantic -fPIC

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

