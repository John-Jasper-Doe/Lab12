# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/libasync")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_library(async SHARED ${ALL_CXX_SOURCE_FILES})
target_include_directories(async PRIVATE ${LIBRARY_INCLUDE_PATH})
target_link_libraries(async
  pthread
)

set_target_properties(
  async
  PROPERTIES
    PUBLIC_HEADER ${LIBRARY_INCLUDE_PATH}/libasync/async/async.hpp)

# install
install(
  TARGETS async
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
