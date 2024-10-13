cmake_minimum_required(VERSION 3.18)

project(core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(core SHARED ${SOURCES})
target_include_directories(core PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE src)

include(GNUInstallDirs)

install(TARGETS core
    EXPORT coreConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core)
install(EXPORT coreConfig DESTINATION share/core/cmake)
export(TARGETS core FILE coreConfig.cmake)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp" "src/*.cpp")
add_executable(coreTest ${TEST_SOURCES})
target_include_directories(coreTest PRIVATE include)