set(PROJECT_NAME LearningOpenGL)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Include/Camera.h"
    "Include/EBO.h"
    "Include/Mesh.h"
    "Include/PCH.h"
    "Include/Platform.h"
    "Include/Shader.h"
    "Include/VAO.h"
    "Include/VBO.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Resource_Files__Meshes
    "Resources/Meshes/bunny.bin"
    "Resources/Meshes/bunny.gltf"
)
source_group("Resource Files\\Meshes" FILES ${Resource_Files__Meshes})

set(Resource_Files__Shaders
    "Resources/Shaders/sample.frag"
    "Resources/Shaders/sample.vert"
)
source_group("Resource Files\\Shaders" FILES ${Resource_Files__Shaders})

set(Source_Files
    "Source/Camera.cpp"
    "Source/EBO.cpp"
    "Source/glad.c"
    "Source/Main.cpp"
    "Source/Mesh.cpp"
    "Source/PCH.cpp"
    "Source/Platform.cpp"
    "Source/Shader.cpp"
    "Source/stb.c"
    "Source/VAO.cpp"
    "Source/VBO.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Resource_Files__Meshes}
    ${Resource_Files__Shaders}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Include/PCH.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE LearningOpenGL)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/Build/${PROJECT_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Build/${PROJECT_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(Source/glad.c ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(Source/stb.c ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /DEBUG;
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "glfw3;"
    "opengl32"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

