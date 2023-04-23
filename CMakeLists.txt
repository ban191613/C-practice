project(Cmake_Cpp)
aux_source_directory(src SRC_SUB)  #搜索 dir 目录下所有的源文件，并将结果列表存储在变量 VAR 中
aux_source_directory(. SRC_CUR)

add_executable(Cmake_Cpp ${SRC_SUB} ${SRC_CUR})   #定使用源文件 src，生成可执行程序 target , ${变量名} 是取变量的值

include_directories(include) # 设置包含的头文件目录