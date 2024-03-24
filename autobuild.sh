#!/bin/bash  
  
set -e  
# set -x  # 如果需要调试，可以取消注释这行  
  
mkdir -p build  
cd build  
  
cmake ..  
make  
  
echo "项目构建成功"