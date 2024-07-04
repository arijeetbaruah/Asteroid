cmake_minimum_required(VERSION 3.16)
project(AsteroidGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_Declare(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(SFML GLM)

# Set Boost root directory
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/plugins/boost_1_85_0/build)

# Find Boost components
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_subdirectory(plugins/spdlog)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE HEADERS_PP "include/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(
    "src"
)

add_executable(AsteroidGame ${HEADERS} ${HEADERS_PP} ${SOURCES})
target_link_libraries(AsteroidGame PRIVATE sfml-graphics)
target_link_libraries(AsteroidGame PRIVATE sfml-audio)
target_link_libraries(AsteroidGame PRIVATE glm::glm)
target_link_libraries(AsteroidGame PRIVATE spdlog::spdlog)
target_link_libraries(AsteroidGame PRIVATE ${Boost_LIBRARIES})
target_compile_features(AsteroidGame PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET AsteroidGame
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:AsteroidGame>
        VERBATIM)
endif()

