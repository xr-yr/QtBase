set(BUILD_GMOCK OFF)

set(GOOGLETEST_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/googletest-1.15.0)
# file(GLOB GTEST_LIB CONFIGURE_DEPENDS ${GOOGLETEST_DIR}/lib/*)

add_executable(my_test test.cpp add.cpp add.h)
target_include_directories(my_test PUBLIC ${GOOGLETEST_DIR}/include)
target_link_directories(my_test PUBLIC ${GOOGLETEST_DIR}/lib)

# 动态库
# target_link_libraries(my_test PUBLIC gtest gtest_main)
# 静态库 动态库也存在时，链接动态库
target_link_libraries(my_test PUBLIC libgtest.a libgtest_main.a)

# 在Windows系统中，CMake默认不支持Linux风格的RPATH机制，而是依赖于环境变量PATH和PATH环境变量中的DLL目录来定位动态库
# set_target_properties(my_test PROPERTIES INSTALL_RPATH ${GOOGLETEST_DIR}/bin)

# target_link_libraries(my_test PUBLIC ${GTEST_LIB})

add_test(NAME my_test COMMAND my_test)
