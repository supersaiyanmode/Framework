
# Define executable name
BIN = build/libjsontool.so
TEST = test/a.out

# Define source files
SRCS = ./src/JSON.cpp ./src/JSONArray.cpp ./src/JSONObject.cpp ./src/JSONParser.cpp
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

TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Do not make any changes below!
OBJS      = $(SRCS:.cpp=.o)
CXX       = g++
DEP_FILE  = .depend

.PHONY = all clean distclean


# Main entry point
#
all: depend $(BIN) $(TEST)


# For linking object file(s) to produce the executable
#
$(BIN): $(OBJS)
	@echo Linking $@
	@mkdir -p build/include
	@$(CXX) $(LINKFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@
	@cp -R include build/.

$(TEST): $(TEST_OBJS)
	@echo Making tests
	@mkdir -p test/lib
	@cp -R build/libjsontool.so test/lib/.
	@$(CXX) $^ -L test/lib -ljsontool -o $@
	

# For compiling source file(s)
#
.cpp.o:
	@echo Compiling $<
	@$(CXX) -c $(COMPILEFLAGS) $(INCPATH) $< -o $(<:.cpp=.o)


# For cleaning up the project
#
clean:
	$(RM) $(OBJS) $(TEST_OBJS)

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

