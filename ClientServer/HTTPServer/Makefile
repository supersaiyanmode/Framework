
# Define executable name
BIN = bin/libhttpserver.so

# Define source files
SRCS = ./src/HTTPParser.cpp ./src/HTTPRequest.cpp ./src/HTTPResponse.cpp ./src/HTTPServiceMapper.cpp ./src/Plugin.cpp ./src/StaticFileHTTPEndPointHandler.cpp ./src/Structure/Block/BlockReader.cpp ./src/Structure/Block/BlockWriter.cpp ./src/Structure/Line/LineReader.cpp ./src/Structure/Line/LineWriter.cpp ./src/ThreadPoolHTTPServer.cpp ./test/main.cpp

# Define header file paths
INCPATH = -I../GenericServer/include -I../../ConfigurationFileParser/include -I../../StringUtils/include -Iinclude/

# Define the -L library path(s)
LDFLAGS = -L../../ConfigurationFileParser/bin -L../../StringUtils/bin -L ../GenericServer/bin

# Define the -l library name(s)
LIBS = -lconfigparser -lstringutils -ltcpserver

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

