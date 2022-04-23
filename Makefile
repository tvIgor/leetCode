#OBJS specifies which files to compile as part of the project
OBJS = leet_code.cpp tools.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I""

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L""

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
#COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -g -std=c++17 -O0

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = leetCode

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)