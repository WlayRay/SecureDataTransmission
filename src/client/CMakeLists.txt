# 定义变量 SRC_LIST，包含当前目录下的所有源文件
aux_source_directory(. SRC_LIST)

# 配置头文件的搜索路径  
include_directories(  
    "${CMAKE_SOURCE_DIR}/include"  
    "${CMAKE_SOURCE_DIR}/include/client"   
    "${CMAKE_SOURCE_DIR}/proto" 
)  

# 查找并链接需要的库   
find_library(SSL_LIB ssl)  
find_library(CRYPTO_LIB crypto)  
find_package(Protobuf REQUIRED)
 
# 设置目标链接库   
set(LIBS ${SSL_LIB} ${CRYPTO_LIB} ${PROTOBUF_LIBRARIES})  

# 添加 protobuf 生成类文件
set(PROTOBUF_FILES 
    "${CMAKE_SOURCE_DIR}/proto/clientrequest.pb.cc" 
    "${CMAKE_SOURCE_DIR}/proto/clientrespond.pb.cc"
)

# 指定可生成文件
add_executable(Client ${SRC_LIST} ${PROTOBUF_FILES})
# 添加目标链接库到链接器   
target_link_libraries(Client ${LIBS} mysqlclient ${PROTOBUF_LIBRARIES})