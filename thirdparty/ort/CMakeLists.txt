cmake_minimum_required(VERSION 3.20)
project(ONNXRuntime)

include(ExternalProject)
find_package(Git)

set(ORT_INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/install")

set(ORT_CONFIG Release)
if(WIN32)
    set(ORT_BUILD_SCRIPT build.bat)
else()
    set(ORT_BUILD_SCRIPT build.sh)
endif()

set(ORT_CONFIGURE_ARGS
    --update
    --compile_no_warning_as_error
    --skip_submodule_sync
    --build_dir <BINARY_DIR>
    --config ${ORT_CONFIG}
    --build_shared_lib
    --use_dnnl
    --compile_no_warning_as_error
    --cmake_extra_defines
        CMAKE_CXX_STANDARD=11
        CMAKE_INSTALL_PREFIX=${ORT_INSTALL_DIR}
        FETCHCONTENT_TRY_FIND_PACKAGE_MODE=NEVER
        onnxruntime_BUILD_UNIT_TESTS=OFF
)

set(ORT_BUILD_ARGS
    --build
    --build_dir <BINARY_DIR>
    --enable_lto
    --skip_tests
    --config ${ORT_CONFIG}
    --parallel
    --compile_no_warning_as_error
    --target install
    --cmake_extra_defines
        CMAKE_CXX_STANDARD=11
)

ExternalProject_Add(onnxruntime_ep
    GIT_REPOSITORY https://github.com/microsoft/onnxruntime.git
    GIT_TAG v1.22.2
    GIT_SHALLOW TRUE
    GIT_SUBMODULES_RECURSE TRUE

    INSTALL_DIR ${ORT_INSTALL_DIR}

    PATCH_COMMAND
        ${GIT_EXECUTABLE} apply
        ${CMAKE_CURRENT_LIST_DIR}/patches/missing-include-cstdint.diff

    CONFIGURE_COMMAND
        <SOURCE_DIR>/${ORT_BUILD_SCRIPT} ${ORT_CONFIGURE_ARGS}

    BUILD_COMMAND
        <SOURCE_DIR>/${ORT_BUILD_SCRIPT} ${ORT_BUILD_ARGS}

    INSTALL_COMMAND ""
)

# Copy DNNL libraries
if(WIN32)
    ExternalProject_Add_Step(onnxruntime_ep copy_lib
        DEPENDEES
            install

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            <BINARY_DIR>/${ORT_CONFIG}/dnnl/install/lib
            <INSTALL_DIR>/lib

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            <BINARY_DIR>/${ORT_CONFIG}/dnnl/install/bin
            <INSTALL_DIR>/bin
    )
else()
    ExternalProject_Add_Step(onnxruntime_ep copy_lib
        DEPENDEES
            install

        COMMAND cp -a
            <BINARY_DIR>/${ORT_CONFIG}/dnnl/install/lib/.
            <INSTALL_DIR>/lib
    )
endif()

