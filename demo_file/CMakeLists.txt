
aux_source_directory(. SRCS_FILE)
add_executable(demo_file ${SRCS_FILE})
#如果不加上下行代码，则会报出“找不到头文件DEMO_FILE”的错误
# target_include_directories(demo_file PUBLIC /home/yangshuo/cmake_demo/demo_file)

