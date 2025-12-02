# CMakeList.txt : CMake project for CSED451, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Enable Hot Reload for MSVC compilers if supported.
project (CSED451)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(RUNTIME_ASSET_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
set(RUNTIME_SHADER_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shader")

include_directories("${CMAKE_SOURCE_DIR}/include")
find_package(OpenGL REQUIRED)

if(WIN32)
    add_library(GLUT SHARED IMPORTED)
    set_target_properties(GLUT PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/win/freeglut.lib"
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/win/freeglut.dll"
    )
    
    add_library(glew SHARED IMPORTED)
    set_target_properties(glew PROPERTIES
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/win/glew32.lib"
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/win/glew32.dll"
    )

    add_library(glm INTERFACE)
    set_target_properties(glm PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/glm"
    )

    configure_file("${CMAKE_SOURCE_DIR}/bin/win/freeglut.dll"
                 "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/freeglut.dll" COPYONLY)
    configure_file("${CMAKE_SOURCE_DIR}/bin/win/glew32.dll"
                 "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glew32.dll" COPYONLY)
elseif(APPLE)
    add_library(GLUT SHARED IMPORTED)
    set_target_properties(GLUT PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/mac/libglut.dylib"
        INTERFACE_LINK_OPTIONS "-framework;GLUT"
    )
    add_library(glew SHARED IMPORTED)
    set_target_properties(glew PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/mac/libGLEW.dylib"
    )
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE "${CMAKE_SOURCE_DIR}/include/glm")
elseif(UNIX)
    add_library(GLUT SHARED IMPORTED)
    set_target_properties(GLUT PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/linux/libglut.so.3.12.0"
        INTERFACE_LINK_OPTIONS "-lglut"
    )

    add_library(glew SHARED IMPORTED)
    set_target_properties(glew PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/linux/libGLEW.so.2.2.0"
        INTERFACE_LINK_OPTIONS "-lGLEW"
    )

    add_library(glu SHARED IMPORTED)
    set_target_properties(glu PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/linux/libGLU.so.1.3.1"
        INTERFACE_LINK_OPTIONS "-lGLU"
    )
    
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE "${CMAKE_SOURCE_DIR}/include/glm")

    link_directories("${CMAKE_SOURCE_DIR}/lib/linux")
    set(SHARED_PATH "${CMAKE_SOURCE_DIR}/bin/linux")
endif()

function(add_gl_executable_single_file exec_name source_file)
  add_executable(${exec_name} ${source_file})
  if(UNIX and NOT APPLE)
    target_link_libraries(${exec_name} OpenGL::GL GLUT glew glu)
  else()
    target_link_libraries(${exec_name} OpenGL::GL GLUT glew)
  endif()
  target_compile_definitions(${exec_name} PRIVATE GL_SILENCE_DEPRECATION)
  if(DEFINED GLM_INCLUDE_DIR)
    target_include_directories(${exec_name} PRIVATE ${GLM_INCLUDE_DIR})
  else()
    target_link_libraries(${exec_name} glm::glm)
  endif()
endfunction()

# Add source to this project's executable.
add_subdirectory(src)

file(
    INSTALL "${CMAKE_SOURCE_DIR}/assets"
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
file(
    INSTALL "${CMAKE_SOURCE_DIR}/src/shader"
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/shader"
    "${RUNTIME_SHADER_DIRECTORY}"
    COMMENT "Updating Shaders..."
)

add_dependencies(touhou_postech CopyShaders)