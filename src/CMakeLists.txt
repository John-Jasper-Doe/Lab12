# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/src")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_executable(${PROJECT_NAME}_m ${ALL_CXX_SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_m PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}_m
  pthread
  ${PROJECT_NAME}
)

