PROJECT(mytest)

aux_source_directory(. SRC)

add_library(mytest ${SRC})

# target_compile_options(mytest PRIVATE -std=c++11)