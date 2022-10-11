cmake_minimum_required(VERSION 3.16)
project(demo VERSION 1.0.0.0)

#打印project相关信息
message(STATUS "......CMAKE_PROJECT_NAME    = ${CMAKE_PROJECT_NAME}")
message(STATUS "......PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message(STATUS "......PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message(STATUS "......PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
message(STATUS "......PROJECT_VERSION_TWEAK = ${PROJECT_VERSION_TWEAK}")

message(STATUS "......PROJECT_HOMEPAGE_URL  = ${PROJECT_HOMEPAGE_URL}")           #没有打印出来
message(STATUS "......CMAKE_PROJECT_DESCRIPTION = ${CMAKE_PROJECT_DESCRIPTION}")  #没有打印出来
message(STATUS "......PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "......PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "......operation system: ${CMAKE_SYSTEM}")

#打印系统平台
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

#配置C++选项
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

# 增加子目录
add_subdirectory(demo_thread)
include_directories(${PROJECT_SOURCE_DIR}/demo_thread)   #这样在main函数中 就可以直接 #include <demo_thread.h>

add_subdirectory(demo_file)

add_subdirectory(demo_beforeMain)

add_subdirectory(demo_c11)

# 源文件
aux_source_directory(. DIR_SRCS)

#增加可执行程序
add_executable(${CMAKE_PROJECT_NAME} ${DIR_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} pthread demo_thread)


