cmake_minimum_required (VERSION 2.6)

set (SRC Piece.cxx)
set (EXE testPiece)
set (EXEGTEST testGtest)

# C++11
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

# target doxygen : doc/html/index.html
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# target valgrind : ctest -D ExperimentalTest -V
find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

# target cppcheck : check/index.html
add_custom_target(cppcheck
# analysis
COMMAND cppcheck -v -f --language=c++ --xml --xml-version=2 --enable=all  ${CMAKE_CURRENT_SOURCE_DIR} 2> check.xml
# htmlreport
COMMAND cppcheck-htmlreport --source-dir=${CMAKE_CURRENT_SOURCE_DIR} --report-dir=check --file=check.xml
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
COMMENT "Running cppcheck to produce code analysis report."
)

# target cov : coverage.html
add_custom_target(cov
# tests
COMMAND ${EXE}
# gcovr
COMMAND lcov --directory ${CMAKE_CURRENT_SOURCE_DIR} --capture --output-file coverage.lcov
COMMAND	python ${CMAKE_CURRENT_SOURCE_DIR}/lcov_cobertura.py coverage.lcov --output coverage.xml
COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --html -o coverage.html --html-details
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
COMMENT "Running gcovr to produce code coverage report."
)

project (Echecs)
use_cxx11()
add_compile_options(-g --coverage)
add_executable(${EXE} ${EXE}.cxx ${SRC})
target_link_libraries(${EXE} --coverage)

enable_testing()
add_test(${EXE} ${EXE})

#find_package(GTest)
set ( GTEST_INCLUDE_DIRS "googletest/googletest/include" )
set ( GTEST_LIB_DIRS "../googletest/build/lib" )
set ( GTEST_LIBRARIES "gtest" )
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${EXEGTEST} ${EXEGTEST}.cxx ${SRC})
target_link_libraries(${EXEGTEST} --coverage -pthread -L${GTEST_LIB_DIRS} ${GTEST_LIBRARIES})
add_test(${EXEGTEST} ${EXEGTEST})
