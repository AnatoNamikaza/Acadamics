# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLION\CLionProjects\TrainProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLION\CLionProjects\TrainProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TrainProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TrainProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TrainProject.dir/flags.make

CMakeFiles/TrainProject.dir/main.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/main.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TrainProject.dir/main.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\main.cpp.obj -c D:\CLION\CLionProjects\TrainProject\main.cpp

CMakeFiles/TrainProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/main.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\main.cpp > CMakeFiles\TrainProject.dir\main.cpp.i

CMakeFiles/TrainProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/main.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\main.cpp -o CMakeFiles\TrainProject.dir\main.cpp.s

CMakeFiles/TrainProject.dir/Person.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/Person.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/Person.cpp.obj: ../Person.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TrainProject.dir/Person.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\Person.cpp.obj -c D:\CLION\CLionProjects\TrainProject\Person.cpp

CMakeFiles/TrainProject.dir/Person.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/Person.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\Person.cpp > CMakeFiles\TrainProject.dir\Person.cpp.i

CMakeFiles/TrainProject.dir/Person.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/Person.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\Person.cpp -o CMakeFiles\TrainProject.dir\Person.cpp.s

CMakeFiles/TrainProject.dir/Adult.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/Adult.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/Adult.cpp.obj: ../Adult.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TrainProject.dir/Adult.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\Adult.cpp.obj -c D:\CLION\CLionProjects\TrainProject\Adult.cpp

CMakeFiles/TrainProject.dir/Adult.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/Adult.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\Adult.cpp > CMakeFiles\TrainProject.dir\Adult.cpp.i

CMakeFiles/TrainProject.dir/Adult.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/Adult.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\Adult.cpp -o CMakeFiles\TrainProject.dir\Adult.cpp.s

CMakeFiles/TrainProject.dir/Kid.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/Kid.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/Kid.cpp.obj: ../Kid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TrainProject.dir/Kid.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\Kid.cpp.obj -c D:\CLION\CLionProjects\TrainProject\Kid.cpp

CMakeFiles/TrainProject.dir/Kid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/Kid.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\Kid.cpp > CMakeFiles\TrainProject.dir\Kid.cpp.i

CMakeFiles/TrainProject.dir/Kid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/Kid.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\Kid.cpp -o CMakeFiles\TrainProject.dir\Kid.cpp.s

CMakeFiles/TrainProject.dir/Bogie.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/Bogie.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/Bogie.cpp.obj: ../Bogie.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TrainProject.dir/Bogie.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\Bogie.cpp.obj -c D:\CLION\CLionProjects\TrainProject\Bogie.cpp

CMakeFiles/TrainProject.dir/Bogie.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/Bogie.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\Bogie.cpp > CMakeFiles\TrainProject.dir\Bogie.cpp.i

CMakeFiles/TrainProject.dir/Bogie.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/Bogie.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\Bogie.cpp -o CMakeFiles\TrainProject.dir\Bogie.cpp.s

CMakeFiles/TrainProject.dir/Train.cpp.obj: CMakeFiles/TrainProject.dir/flags.make
CMakeFiles/TrainProject.dir/Train.cpp.obj: CMakeFiles/TrainProject.dir/includes_CXX.rsp
CMakeFiles/TrainProject.dir/Train.cpp.obj: ../Train.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TrainProject.dir/Train.cpp.obj"
	"D:\program files\minGW\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TrainProject.dir\Train.cpp.obj -c D:\CLION\CLionProjects\TrainProject\Train.cpp

CMakeFiles/TrainProject.dir/Train.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TrainProject.dir/Train.cpp.i"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLION\CLionProjects\TrainProject\Train.cpp > CMakeFiles\TrainProject.dir\Train.cpp.i

CMakeFiles/TrainProject.dir/Train.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TrainProject.dir/Train.cpp.s"
	"D:\program files\minGW\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLION\CLionProjects\TrainProject\Train.cpp -o CMakeFiles\TrainProject.dir\Train.cpp.s

# Object files for target TrainProject
TrainProject_OBJECTS = \
"CMakeFiles/TrainProject.dir/main.cpp.obj" \
"CMakeFiles/TrainProject.dir/Person.cpp.obj" \
"CMakeFiles/TrainProject.dir/Adult.cpp.obj" \
"CMakeFiles/TrainProject.dir/Kid.cpp.obj" \
"CMakeFiles/TrainProject.dir/Bogie.cpp.obj" \
"CMakeFiles/TrainProject.dir/Train.cpp.obj"

# External object files for target TrainProject
TrainProject_EXTERNAL_OBJECTS =

TrainProject.exe: CMakeFiles/TrainProject.dir/main.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/Person.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/Adult.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/Kid.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/Bogie.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/Train.cpp.obj
TrainProject.exe: CMakeFiles/TrainProject.dir/build.make
TrainProject.exe: D:/Libraries/SFML/lib/sfml-graphics-d.lib
TrainProject.exe: D:/Libraries/SFML/lib/sfml-audio-d.lib
TrainProject.exe: D:/Libraries/SFML/lib/sfml-window-d.lib
TrainProject.exe: D:/Libraries/SFML/lib/sfml-network-d.lib
TrainProject.exe: D:/Libraries/TGUI/lib/tgui-d.lib
TrainProject.exe: D:/Libraries/SFML/lib/sfml-system-d.lib
TrainProject.exe: CMakeFiles/TrainProject.dir/linklibs.rsp
TrainProject.exe: CMakeFiles/TrainProject.dir/objects1.rsp
TrainProject.exe: CMakeFiles/TrainProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable TrainProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TrainProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TrainProject.dir/build: TrainProject.exe

.PHONY : CMakeFiles/TrainProject.dir/build

CMakeFiles/TrainProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TrainProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TrainProject.dir/clean

CMakeFiles/TrainProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLION\CLionProjects\TrainProject D:\CLION\CLionProjects\TrainProject D:\CLION\CLionProjects\TrainProject\cmake-build-debug D:\CLION\CLionProjects\TrainProject\cmake-build-debug D:\CLION\CLionProjects\TrainProject\cmake-build-debug\CMakeFiles\TrainProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TrainProject.dir/depend

