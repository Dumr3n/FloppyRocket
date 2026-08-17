include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(FloppyRocketTests GameMathTests.cpp ../Sandbox/src/GameMath.cpp)
target_include_directories(FloppyRocketTests PRIVATE ../Sandbox/src ../Hazel/vendor/glm)
target_link_libraries(FloppyRocketTests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(FloppyRocketTests)
