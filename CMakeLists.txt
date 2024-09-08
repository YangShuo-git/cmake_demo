cmake_minimum_required(VERSION 3.16)
project(CAMKE_DEMO VERSION 1.0.0.0)

#打印project相关信息
message(STATUS "......CMAKE_PROJECT_NAME    = ${CMAKE_PROJECT_NAME}")
message(STATUS "......PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message(STATUS "......PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message(STATUS "......PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
message(STATUS "......PROJECT_VERSION_TWEAK = ${PROJECT_VERSION_TWEAK}")

message(STATUS "......PROJECT_HOMEPAGE_URL  = ${PROJECT_HOMEPAGE_URL}")           #没有设置
message(STATUS "......CMAKE_PROJECT_DESCRIPTION = ${CMAKE_PROJECT_DESCRIPTION}")  #没有设置
message(STATUS "......PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "......PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "......operation system: ${CMAKE_SYSTEM}")

#打印当前系统平台
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

##################################################################

# 1.option来接收 cmake -D 的传参； 不用option也能接收传进来的参数 故注释
# option(demo_test "Enable demo_test" OFF)
# option(demo_stl "Enable demo_stl" OFF)

# 2.设置编译开关 将编译的项目置为ON，才会执行add_subdirectory（增加子目录）
# 已修改为 ./cmake.sh传参的方式，故注释
# set(demo_test OFF)
# set(demo_file OFF)
# set(demo_beforeMain OFF)
# set(demo_class OFF)
# set(demo_stl OFF)
# set(demo_smartPoint OFF)
# set(demo_rvalueRef OFF)
# set(demo_thread OFF)

# 直接接收从cmake.sh传进来的参数
if(demo_test)
    add_subdirectory(demo_test)
endif()

if(demo_file)
    add_subdirectory(demo_file)
endif()

if(demo_beforeMain)
    add_subdirectory(demo_beforeMain)
endif()

if(demo_class)
    add_subdirectory(demo_class)
endif()

if(demo_stl)
    add_subdirectory(demo_stl)
endif()

if(demo_smartPoint)
    add_subdirectory(demo_smartPoint)
endif()

if(demo_thread)
    add_subdirectory(demo_thread)

    # 添加头文件目录
    # 这样在main函数中就不用写绝对路径，可以直接 #include <demo_thread.h>
    include_directories(${PROJECT_SOURCE_DIR}/demo_thread)
endif()

if(demo_struct)
    add_subdirectory(demo_struct)
endif()


# 添加源文件
aux_source_directory(. DIR_SRCS)

# 最终生成可执行程序（也可以不生成，直接用上面单独的项目生成的可执行程序）
add_executable(${CMAKE_PROJECT_NAME} ${DIR_SRCS})

# if(demo_thread)
#     # 给可执行程序添加链接库
#     target_link_libraries(${CMAKE_PROJECT_NAME} pthread demo_thread)
# endif()


