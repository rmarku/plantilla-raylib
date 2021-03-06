
if(${PLATFORM} MATCHES "Web")
    set(PLATFORM_CPP "PLATFORM_WEB")
    set(GRAPHICS "GRAPHICS_API_OPENGL_ES2")
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_MEMORY=33554432")
    # Since WASM is used, ALLOW_MEMORY_GROWTH has no extra overheads
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/resources/shell.html")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    #set(EXECUTABLE 'index')



endif()