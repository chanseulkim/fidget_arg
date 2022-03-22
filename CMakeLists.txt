cmake_minimum_required(VERSION 2.6...3.8)

project(fidget_arg VERSION 0.0.1)
message(STATUS "Project " ${PROJECT_NAME}) 

# set(librshp_dir "${thirdparty_dir}/librshp")
#set(CMAKE_CXX_FLAGS -pthread)

add_compile_options(
  -Wall 
  -std=c++14
  -fPIC 
)
# if (DEFINED WIN32)
# else()
#   add_compile_options(
#     -ldl 
#     -lpthread
#   )
# endif()

# if (DEFINED DEBUG or DEFINED Debug)
# else()
#   add_compile_options(-O2)
# endif()
include_directories (${PROJECT_SOURCE_DIR})

file(GLOB srcs
  "*.cpp"
)

set (CMAKE_BUILD_TYPE Debug)
message(STATUS "CMAKE_BUILD_TYPE : " ${CMAKE_BUILD_TYPE}) 

add_executable (${PROJECT_NAME} ${srcs})
# add_library(${PROJECT_NAME} SHARED ${srcs})
# add_library(${PROJECT_NAME} STATIC ${srcs})

# target_link_libraries(${PROJECT_NAME} PUBLIC 
#                       ${librshp_files} 
#                       )

