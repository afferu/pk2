cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

Project("PK2_N"
	VERSION 0.0.0.1 
	DESCRIPTION "PekkaKana2 game and toolset."
	LANGUAGES CXX
)

include(FetchContent)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(FindGTest)
    include(CTest)
	enable_testing()
	find_package(GTest CONFIG REQUIRED)
endif()

#PisteEngine 
add_subdirectory("PisteEngine")

#PekkaKana2
#add_subdirectory("PekkaKana2")

#Level editor
#add_subdirectory("PK2LevelEditor")

#Sprite creator
#add_subdirectory("PK2SpriteCreator")