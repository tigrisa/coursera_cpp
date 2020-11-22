cmake_minimum_required(VERSION 3.10)
project(server_stats VERSION 0.1.0)

# include(CTest)
# enable_testing()
set(SOURCES server_stats.cpp stats.cpp ${PROJECT_SOURCE_DIR}/stats.h ${PROJECT_SOURCE_DIR}/http_request.h)
add_executable(server_stats ${SOURCES})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

