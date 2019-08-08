cmake_minimum_required(VERSION 3.2)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_CMAKE_VAR $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(TRAVIS_BUILD_CMAKE_VAR 999)
endif()

project(allocator VERSION 0.0.${TRAVIS_BUILD_CMAKE_VAR})

message("Version ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(./googletest)

add_executable(allocator "main.cpp")
add_library(allocator_lib "lib.cpp")
add_executable(tests_default tests_default.cpp)

set_target_properties(allocator allocator_lib tests_default PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_link_libraries(allocator PRIVATE
    allocator_lib
)
target_link_libraries(tests_default PRIVATE
    gtest_main
    allocator_lib
)

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(allocator_lib PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

enable_testing()

add_test(tests_default tests_default)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "Felix Palta <my@email.com>")

include(CPack)
