# CMake file for test directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/test")

addtest("alltests"
  testreader.cpp
  testcmdpool.cpp
  testcounter.cpp
  testtsqueue.cpp
  testtaskpool.cpp
  testsplit.cpp
  ${PROJECT_SRC}
)
