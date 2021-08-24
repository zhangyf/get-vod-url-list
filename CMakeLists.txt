cmake_minimum_required(VERSION 3.10)

# set project name and version
project(get_vod_url_list)

set (AR_VERSION_MAJOR 1)
set (AR_VERSION_MINOR 0)

#################################
# GDB 设置
#################################
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/get_vod_url_list.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")

if(APPLE)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
elseif(UNIX)
        include_directories(${PROJECT_SOURCE_DIR}/src/include
                    ${PROJECT_SOURCE_DIR}/src/include/http
                    ${PROJECT_SOURCE_DIR}/src/include/task
                    ${PROJECT_SOURCE_DIR}/3rd_party/linux/include
                    /usr/local/include
                    /usr/local/include/opencv4)
        link_directories(/usr/local/lib
                     ${PROJECT_SOURCE_DIR}/3rd_party/linux/lib
                     /opt/homebrew/Cellar/openssl@1.1/1.1.1k/lib)
endif()

#################################
# 生成可执行文件
#################################
add_executable(get_vod_url_list ${SRC_LIST})

target_link_libraries(get_vod_url_list
                        curl
                        curlpp)

