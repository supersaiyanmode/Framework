
# Define executable name
BIN = a.out

# Define source files
SRCS = ./main.cpp

# Define header file paths
INCPATH = -I../../../ConfigurationFileParser/include -I../../../StringUtils/include -I../include/ -I../../GenericServer/include

# Define the -L library path(s)
LDFLAGS = -L ../bin/ -L ../../GenericServer/bin/ -L ../../../ConfigurationFileParser/bin -L ../../../StringUtils/bin

# Define the -l library name(s)
LIBS = -ltcpserver -lhttpserver -lstringutils -lconfigparser

# Define Compile Flags
COMPILEFLAGS = -g -Wall -pedantic

# Define Link Flags
LINKFLAGS = -pg -Wl,-rpath,../lib

# Do not make any changes below!
OBJS      = $(SRCS:.cpp=.o)
CXX       = g++
DEP_FILE  = .depend

.PHONY = all clean distclean


# Main entry point
#
all: depend $(BIN)
	@mkdir -p bin
	@cp -L ../bin/libhttpserver.so ../../GenericServer/bin/libtcpserver.so ../../../ConfigurationFileParser/bin/libconfigparser.so ../../../StringUtils/bin/libstringutils.so bin/.


# For linking object file(s) to produce the executable
#
$(BIN): $(OBJS)
	@echo Linking $@
	@mkdir -p bin
	@cp -L ../bin/libhttpserver.so ../../GenericServer/bin/libtcpserver.so ../../../ConfigurationFileParser/bin/libconfigparser.so ../../../StringUtils/bin/libstringutils.so bin/.
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

