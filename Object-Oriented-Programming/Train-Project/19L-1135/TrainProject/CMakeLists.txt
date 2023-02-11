cmake_minimum_required(VERSION 3.13)
project(TrainProject)

set(CMAKE_CXX_STANDARD 17)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/Libraries/SFML/lib/cmake/SFML")
set(TGUI_DIR "D:/Libraries/TGUI/lib/cmake/TGUI")

#set(SFML_STATIC_LIBRARIES TRUE)
#set(TGUI_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics audio window system network)
find_package(TGUI)
add_executable(TrainProject main.cpp Person.cpp Person.h Adult.cpp Adult.h Kid.cpp Kid.h Bogie.cpp Bogie.h Train.cpp Train.h)
target_link_libraries(TrainProject sfml-graphics sfml-audio sfml-window sfml-system sfml-network tgui)