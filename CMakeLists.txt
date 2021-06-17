cmake_minimum_required(VERSION 3.19)

project(EmbeddedIntentDetection CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "main.cpp")

include_directories(Emd_Intent_Recognizer/header)

add_subdirectory(Emd_Intent_Recognizer)

add_executable(EmbeddedIntentDetection ${Sources})
target_link_libraries(EmbeddedIntentDetection PUBLIC
	EmbeddedIntentRecogniserLib
)
