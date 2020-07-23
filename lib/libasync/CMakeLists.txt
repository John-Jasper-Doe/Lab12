# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/libasync")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_library(${PROJECT_NAME} SHARED ${ALL_CXX_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME}
  pthread
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    PUBLIC_HEADER ${LIBRARY_INCLUDE_PATH}/libasync/async/async.hpp)

# install
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
