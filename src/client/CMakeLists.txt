# 定义变量SRC_LIST，包含当前目录下的所有源文件
aux_source_directory(. SRC_LIST)

# 指定可生成文件
add_executable(Client ${SRC_LIST})

# 配置头文件的搜索路径  
include_directories(  
    "${CMAKE_SOURCE_DIR}/include"   
    "${CMAKE_SOURCE_DIR}/include/client"  
)  

# 查找并链接需要的库  
find_library(SSL_LIB ssl)  
find_library(CRYPTO_LIB crypto)  
  
# 设置目标链接库  
set(LIBS ${SSL_LIB} ${CRYPTO_LIB})  

# 添加目标链接库到链接器  
target_link_libraries(Client ${LIBS}) 