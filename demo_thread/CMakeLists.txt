
aux_source_directory(. DEMO_THREAD)
add_library(demo_thread SHARED ${DEMO_THREAD})
target_include_directories(demo_thread PUBLIC /home/yangshuo/cmake_demo/demo_thread)

