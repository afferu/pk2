cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

Project("PisteEngine"
	VERSION 0.0.0.1 
	DESCRIPTION "PisteEngine game engine."
	LANGUAGES CXX
)

set(PisteEngineLibName "PisteEngine")

add_library(${PisteEngineLibName} STATIC 
	#"${PROJECT_SOURCE_DIR}/src/Game.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteDraw.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteFont.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteInput.cpp"
	"${PROJECT_SOURCE_DIR}/src/PisteLanguage.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteLog.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteSFX.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteSound.cpp"
	#"${PROJECT_SOURCE_DIR}/src/PisteWait.cpp"
)

target_include_directories(${PisteEngineLibName} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_compile_features(${PisteEngineLibName} PUBLIC cxx_std_17)
set_target_properties(${PisteEngineLibName} PROPERTIES CXX_EXTENSIONS OFF)
target_compile_definitions(${PisteEngineLibName} PRIVATE 
	$<$<CONFIG:Debug>:DEBUG>
)

#Piste::Engine library name alias
add_library(Piste::Engine ALIAS ${PisteEngineLibName})

#Test targets
if(BUILD_TESTING)
	
	set(PisteLanguageTestExec "piste_lang_test")
	add_executable(${PisteLanguageTestExec} "${PROJECT_SOURCE_DIR}/test_src/PisteLanguageTest.cpp")
	target_link_libraries(${PisteLanguageTestExec} PRIVATE
		Piste::Engine
		GTest::GTest 
		GTest::Main
	)
	target_compile_features(${PisteLanguageTestExec} PUBLIC cxx_std_17)
	set_target_properties(${PisteLanguageTestExec} PROPERTIES CXX_EXTENSIONS OFF)
	add_test(NAME "PisteLanguageTest" COMMAND ${PisteLanguageTestExec} "${PROJECT_SOURCE_DIR}/language_test.lng")


endif()

#TODO installation