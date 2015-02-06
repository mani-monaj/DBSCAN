cmake_minimum_required(VERSION 2.8)
project(DBSCAN)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -pedantic -fPIC -pedantic -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -fPIC -pedantic -march=native")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -march=native")

set(WITH_OPENMP 1 CACHE BOOL "Build with OpenMP Support")
set(BUILD_PYTHONLIB 0 CACHE BOOL "Build python bindings")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if(WITH_OPENMP)
  # check for OpenMP
  find_package(OpenMP)
  if(OPENMP_FOUND)
    add_definitions(-DUSE_OPENMP)
    message(STATUS "Enabling OpenMP support")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    message(STATUS "OpenMP CXX Flags: ${OpenMP_CXX_FLAGS}")
    message(STATUS "OpenMP Link Flags: ${CMAKE_EXE_LINKER_FLAGS}")
  else()
    message(STATUS "OpenMP not found. Disabling OpenMP support")
  endif()
else()
  message(STATUS "OpenMP Support is Disabled")
endif(WITH_OPENMP)

add_definitions(-DBOOST_UBLAS_NDEBUG)

add_library(dbscan SHARED src/dbscan.cpp)
include_directories(${DBSCAN_SOURCE_DIR}/include)

add_executable(test_dbscan src/test_dbscan.cpp)
target_link_libraries(test_dbscan dbscan)

set(DBSCAN_INSTALL_TARGETS "dbscan")

if (BUILD_PYTHONLIB)
  find_package(Boost REQUIRED COMPONENTS python)
  find_package(PythonInterp)
  find_package(PythonLibs)
  if (PYTHONLIBS_FOUND AND Boost_FOUND)
    include_directories(
      ${PYTHON_INCLUDE_PATH}
    )

    add_library(pydbscan SHARED src/PyDBSCAN.cpp)
    target_link_libraries(pydbscan dbscan boost_python)

    set_target_properties(pydbscan
      PROPERTIES
          MAJOR_VERSION 1
          MINOR_VERSION 0
              LIBRARY_OUTPUT_NAME pydbscan
              PREFIX ""
    )

    set(DBSCAN_INSTALL_TARGETS "${DBSCAN_INSTALL_TARGETS} pydbscan")
  endif(PYTHONLIBS_FOUND AND Boost_FOUND)
endif(BUILD_PYTHONLIB)

install(TARGETS ${DBSCAN_INSTALL_TARGETS}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES include/dbscan/dbscan.h
  DESTINATION include/dbscan
)
