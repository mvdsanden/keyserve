cmake_minimum_required(VERSION 3.7)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

include(mvds)

mvds_thirdparty_include_dir("${CMAKE_CURRENT_LIST_DIR}/thirdparty/GSL/include")
mvds_thirdparty_include_dir("${CMAKE_CURRENT_LIST_DIR}/thirdparty/spdlog/include")

mvds_build()
