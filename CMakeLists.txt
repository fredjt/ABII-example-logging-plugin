cmake_minimum_required(VERSION 3.28)

project(example_logger LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

if (BIT32)
	list(PREPEND CMAKE_PREFIX_PATH "/usr/lib32/cmake/abii")
endif ()
find_package(abii REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	message(STATUS "Enabling LTO for non-debug builds")
	set(CMAKE_OPTIMIZE_DEPENDENCIES TRUE)
	add_compile_options("-flto" "-ffat-lto-objects" "-O3")
endif ()

add_library(example_logger SHARED include/bits/dlfcn.h include/header.cpp include/header.h)

target_link_libraries(example_logger PUBLIC abii::libabii)

if (BIT32)
	set_target_properties(example_logger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	add_compile_definitions("BIT32")
endif ()

target_include_directories(example_logger PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# CPack setup
if (BIT32)
	set(CPACK_PACKAGE_NAME "abii-example-logging-plugin-32")
else ()
	set(CPACK_PACKAGE_NAME "abii-example-logging-plugin")
endif ()
set(CPACK_PACKAGE_VENDOR "Trent Tanchin")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ABII-example-logging-plugin - Example logging plugin for ABII")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Trent Tanchin <trent@tanchin.org>")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}")

set(CPACK_SOURCE_IGNORE_FILES
    /build/
    /cmake-build-.*/
    /.git/
    /.idea/
    ~$)

include(CPack)

if (BIT32)
	set(CMAKE_INSTALL_PLUGINDIR "share/abii/32")
else ()
	set(CMAKE_INSTALL_PLUGINDIR "share/abii/64")
endif ()
install(TARGETS example_logger LIBRARY DESTINATION ${CMAKE_INSTALL_PLUGINDIR})
