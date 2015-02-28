WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall
RESINC =
LIBDIR =
LIB =
LDFLAGS =

INC_DEBUG = $(INC) -Iinclude -I../OGameExpeditionBot
CFLAGS_DEBUG = $(CFLAGS) -std=c++11 -g -DDEBUG -DCLASS_STATUSPRINTING
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB) -lPocoFoundation -lPocoNet
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/OGame\ Expedition\ Bot

INC_RELEASE = $(INC) -Iinclude -I../OGameExpeditionBot
CFLAGS_RELEASE = $(CFLAGS) -O2 -std=c++11 -g
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB) -lPocoFoundation -lPocoNet
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/OGame\ Expedition\ Bot

OBJ_DEBUG = $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/src/OGameSession.o $(OBJDIR_DEBUG)/src/Position.o $(OBJDIR_DEBUG)/src/Resources.o $(OBJDIR_DEBUG)/src/ShipsParser.o $(OBJDIR_DEBUG)/src/FleetVariables.o $(OBJDIR_DEBUG)/src/Functions.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/src/OGameSession.o $(OBJDIR_RELEASE)/src/Position.o $(OBJDIR_RELEASE)/src/Resources.o $(OBJDIR_RELEASE)/src/ShipsParser.o $(OBJDIR_RELEASE)/src/FleetVariables.o $(OBJDIR_RELEASE)/src/Functions.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/src/OGameSession.o: src/OGameSession.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/OGameSession.cpp -o $(OBJDIR_DEBUG)/src/OGameSession.o

$(OBJDIR_DEBUG)/src/Position.o: src/Position.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/Position.cpp -o $(OBJDIR_DEBUG)/src/Position.o

$(OBJDIR_DEBUG)/src/Resources.o: src/Resources.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/Resources.cpp -o $(OBJDIR_DEBUG)/src/Resources.o

$(OBJDIR_DEBUG)/src/ShipsParser.o: src/ShipsParser.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/ShipsParser.cpp -o $(OBJDIR_DEBUG)/src/ShipsParser.o

$(OBJDIR_DEBUG)/src/FleetVariables.o: src/FleetVariables.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/FleetVariables.cpp -o $(OBJDIR_DEBUG)/src/FleetVariables.o

$(OBJDIR_DEBUG)/src/Functions.o: src/Functions.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/Functions.cpp -o $(OBJDIR_DEBUG)/src/Functions.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/src/OGameSession.o: src/OGameSession.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/OGameSession.cpp -o $(OBJDIR_RELEASE)/src/OGameSession.o

$(OBJDIR_RELEASE)/src/Position.o: src/Position.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/Position.cpp -o $(OBJDIR_RELEASE)/src/Position.o

$(OBJDIR_RELEASE)/src/Resources.o: src/Resources.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/Resources.cpp -o $(OBJDIR_RELEASE)/src/Resources.o

$(OBJDIR_RELEASE)/src/ShipsParser.o: src/ShipsParser.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/ShipsParser.cpp -o $(OBJDIR_RELEASE)/src/ShipsParser.o

$(OBJDIR_RELEASE)/src/FleetVariables.o: src/FleetVariables.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/FleetVariables.cpp -o $(OBJDIR_RELEASE)/src/FleetVariables.o

$(OBJDIR_RELEASE)/src/Functions.o: src/Functions.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/Functions.cpp -o $(OBJDIR_RELEASE)/src/Functions.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)/src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

