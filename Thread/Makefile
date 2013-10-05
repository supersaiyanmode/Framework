
# Define executable name
BIN = bin/libthreadingutil.so

# Define source files
SRCS = ./src/Condition.cpp ./src/Mutex.cpp ./src/ReadWriteLock.cpp ./src/test/prodcons.cpp ./src/test/ThreadPoolTest.cpp ./src/test/ThreadTest.cpp ./src/Thread.cpp ./src/ThreadLogger.cpp

# Define header file paths
INCPATH = -I./include -I ../Time/include

# Define the -L library path(s)
LDFLAGS = 

# Define the -l library name(s)
LIBS = -lpthread

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

