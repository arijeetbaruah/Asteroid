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
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(SFML GLM yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

add_subdirectory(plugins/spdlog)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE HEADERS_PP "include/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

file(GLOB_RECURSE RESOURCES "assets/*.rc")
file(GLOB_RECURSE RESOURCES_HEADER "assets/*.h")

include_directories(
    "src"
)

add_executable(AsteroidGame ${HEADERS} ${HEADERS_PP} ${SOURCES} ${RESOURCES} ${RESOURCES_HEADER})
target_link_libraries(AsteroidGame PRIVATE sfml-graphics)
target_link_libraries(AsteroidGame PRIVATE sfml-audio)
target_link_libraries(AsteroidGame PRIVATE glm::glm)
target_link_libraries(AsteroidGame PRIVATE spdlog::spdlog)
target_link_libraries(AsteroidGame PRIVATE yaml-cpp::yaml-cpp)
target_compile_features(AsteroidGame PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET AsteroidGame
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:AsteroidGame>
        VERBATIM)
endif()

