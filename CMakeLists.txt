cmake_minimum_required(VERSION 3.14)
project(MocliaDice)

set(CMAKE_CXX_STANDARD 17)

# 不要构建 mirai-cpp 自带的 examples
set(MIRAI_CPP_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)

add_subdirectory(extern/MocliaDiceCore)
add_subdirectory(extern/mirai-cpp)

# 递归搜索 src 目录中的源文件
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 设置头文件目录
include_directories(include)

target_link_libraries(${PROJECT_NAME} PRIVATE mirai-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE MocliaDiceCore)

# 使用 mirai-cpp 静态库
target_compile_definitions(${PROJECT_NAME} PRIVATE MIRAICPP_STATICLIB)

# gcc 要连接 pthread
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
