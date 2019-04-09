cmake_minimum_required(VERSION 3.13)
project(algorithm)

set(CMAKE_CXX_STANDARD 14)

# 可执行文件生成，凡是要编译的源文件都需要列举出来
# 项目名称+空格+路径+文件+后缀
add_executable(algorithm data_structure_common.c data_structure_func.h data_structure_func_impl.c thread_binary_tree.c)
#add_executable(algorithm sort_type.h sort_type.c)