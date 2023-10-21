cmake_minimum_required(VERSION 3.13)
project(DSA4Anato)

set(CMAKE_CXX_STANDARD 14)

#add_executable(DSA4Anato main.cpp DList.h DList.cpp Doc_Data.h Doc_Data.cpp Doc_Info.h Doc_Info.cpp Node.h Node.cpp
#        "Search Engine.h" "Search Engine.cpp" Term_Info.h Term_Info.cpp AVL.cpp AVL.h ANode.cpp ANode.h)

add_executable(DSA4Anato AVL.h AVLNode.h DList.h Doc_Data.h Doc_Info.h Node.h "Search Engine.h" Term_Info.h main.cpp)