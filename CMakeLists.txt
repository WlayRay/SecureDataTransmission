# 设置CMake的最低版本要求  
cmake_minimum_required(VERSION 3.0)  
  
# 定义项目名称  
project(secure)  
  
# 配置编译选项，添加调试标志  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  
  
# 设置可执行文件最终的输出路径  
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")  
  
# 指定搜索（加载）的子目录  
add_subdirectory(src)