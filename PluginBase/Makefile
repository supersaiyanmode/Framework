#Below variable declarations will be maintained in all future Makefiles generated
LIBS=
CPPCOMPILER=g++
CCOMPILER=gcc
COMPILEFLAGS=-Wall -g -O3
DEFINES=ADDER_TEST

#Do not make any changes below!!
PREPROCESSORDEFINES=$(patsubst %,-D%,$(DEFINES))

all : obj/main.o obj/Plugin.o 
	$(CPPCOMPILER) $(COMPILEFLAGS) obj/main.o obj/Plugin.o $(LIBS)

obj/main.o : main.cpp  \
		SamplePlugin/AdderPlugin/AdderPlugin.h \
		SamplePlugin/AdderPlugin/MathHelper.h \
		Plugin.h \
		SamplePlugin/AdderPlugin/SubtractorPlugin.h \
		#SamplePlugin/ParameterizedPlugin/ParameterizedPlugin.h \
		Plugin.h
	@mkdir -p obj
	$(CPPCOMPILER) $(COMPILEFLAGS) $(PREPROCESSORDEFINES) -c main.cpp -o obj/main.o

obj/Plugin.o : Plugin.cpp  \
		Plugin.h
	@mkdir -p obj
	$(CPPCOMPILER) $(COMPILEFLAGS) $(PREPROCESSORDEFINES) -c Plugin.cpp -o obj/Plugin.o

add : SamplePlugin/AdderPlugin/AdderPlugin.cpp SamplePlugin/AdderPlugin/AdderPlugin.h SamplePlugin/AdderPlugin/MathHelper.h 
	g++ -shared -fPIC -fvisibility=hidden Plugin.cpp SamplePlugin/AdderPlugin/AdderPlugin.cpp  -o SamplePlugin/AdderPlugin/add.so

subtract : SamplePlugin/AdderPlugin/SubtractorPlugin.cpp SamplePlugin/AdderPlugin/SubtractorPlugin.h SamplePlugin/AdderPlugin/MathHelper.h 
	g++ -shared -fPIC -fvisibility=hidden Plugin.cpp SamplePlugin/AdderPlugin/SubtractorPlugin.cpp  -o SamplePlugin/AdderPlugin/subtract.so

param : SamplePlugin/ParamPlugin/ParamPlugin.cpp SamplePlugin/ParamPlugin/ParamPlugin.h
	g++ -shared -fPIC -fvisibility=hidden Plugin.cpp SamplePlugin/ParamPlugin/ParamPlugin.cpp  -o SamplePlugin/ParamPlugin/param.so

clean:
	@rm -rf obj
	@rm -rf SamplePlugin/AdderPlugin/*.so
	@rm -rf SamplePlugin/ParamPlugin/*.so
	@echo Cleaned!
