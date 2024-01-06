
aux_source_directory(. SRCS_THREAD)
add_library(demo_thread SHARED ${SRCS_THREAD})

#如果不加上下行代码，则会报出“找不到头文件demo_thread”的错误 需要找原因
target_include_directories(demo_thread PUBLIC /home/yangshuo/cmake_demo/demo_thread)