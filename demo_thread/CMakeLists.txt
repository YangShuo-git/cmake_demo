
aux_source_directory(. SRCS_FILE)
# add_library(demo_thread SHARED ${SRCS_THREAD})
add_executable(demo_thread ${SRCS_FILE})

#如果不加上下行代码，则会报出“找不到头文件demo_thread”的错误 需要找原因
target_include_directories(demo_thread PUBLIC /home/yangshuo/cmake_demo/demo_thread)

# 不加则报错 undefined reference to `pthread_create'  
# 原因： linux下用gcc或clang必须加-pthread连接到线程库，否则会出错
target_link_libraries(demo_thread pthread)
