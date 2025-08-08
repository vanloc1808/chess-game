cmake_minimum_required(VERSION 3.15)
project(ChessGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Allow user to point to a custom SFML root on Windows or other systems
set(SFML_DIR_HINT "" CACHE PATH "Optional hint path to SFML cmake config (e.g. C:/SFML/lib/cmake/SFML)")
if(SFML_DIR_HINT)
  list(APPEND CMAKE_PREFIX_PATH "${SFML_DIR_HINT}")
endif()

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

file(GLOB SOURCE_FILES
  "sources/*.cpp"
)

add_executable(chess ${SOURCE_FILES})
target_include_directories(chess PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sources)
target_link_libraries(chess PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# On macOS, make the app bundle locate resources relative to working dir
if(APPLE)
  set_target_properties(chess PROPERTIES
    MACOSX_BUNDLE FALSE
  )
endif()

# Install target and resources (optional)
install(TARGETS chess RUNTIME DESTINATION bin)
install(DIRECTORY resources/ DESTINATION resources)


