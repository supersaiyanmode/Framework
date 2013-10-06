
# Define executable name
BIN = a.out

# Define source files
SRCS = ./main.cpp

# Define header file paths
INCPATH = -I ../Client/include -I ../Server/include -I ../../GenericServer/include -I ../../../Random/include \
		-I ../../../Thread/include -I ../../../Time/include -I ../../../OptParse/include \
		-I ../../../StringUtils/include

# Define the -L library path(s)
LDFLAGS = -L ../Client/bin -L ../Server/bin -L ../../GenericServer/bin -L ../../../Random/bin -L ../../../Thread/bin \
		-L ../../../Time/bin -L ../../../OptParse/bin -L ../../../StringUtils/bin

# Define the -l library name(s)
LIBS = -lcmsclient -lcmsserver -ltcpserver -lrandomutil -lthreadingutil -ltimeutil -loptparse -l stringutils

# Define Compile Flags
COMPILEFLAGS = -Wall -pedantic

# Define Link Flags
LINKFLAGS =

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
	@cp ../Client/bin/libcmsclient.so ../Server/bin/libcmsserver.so ../../GenericServer/bin/libtcpserver.so \
	../../../Random/bin/librandomutil.so ../../../Thread/bin/libthreadingutil.so \
	../../../Time/bin/libtimeutil.so ../../../OptParse/bin/liboptparse.so \
	../../../StringUtils/bin/libstringutils.so ../../../ConfigurationFileParser/bin/libconfigparser.so bin/.
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

