cmake_minimum_required(VERSION 3.2)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_CMAKE_VAR $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(TRAVIS_BUILD_CMAKE_VAR 999)
endif()

project(MUH_PROJECT VERSION 0.0.${TRAVIS_BUILD_CMAKE_VAR})

message("Version ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(./googletest)

add_executable(MUH_PROJECT "main.cpp")
add_library(MUH_PROJECT_lib "lib.cpp")
add_executable(tests_default tests_default.cpp)

set_target_properties(MUH_PROJECT MUH_PROJECT_lib tests_default PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_link_libraries(MUH_PROJECT PRIVATE
    MUH_PROJECT_lib
)
target_link_libraries(tests_default PRIVATE
    gtest_main
    MUH_PROJECT_lib
)

if (MSVC)
    target_compile_options(MUH_PROJECT PRIVATE
        /W4
    )
    target_compile_options(MUH_PROJECT_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(MUH_PROJECT PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(MUH_PROJECT_lib PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

enable_testing()

add_test(tests_default tests_default)

install(TARGETS MUH_PROJECT RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "Felix Palta <my@email.com>")

include(CPack)
