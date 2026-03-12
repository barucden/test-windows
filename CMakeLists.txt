cmake_minimum_required(VERSION 3.21)
project(MyTest)

include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

# wxWidgets
set(wxBUILD_SHARED OFF)
set(wxUSE_AUI OFF)
set(wxUSE_HTML OFF)
set(wxUSE_EXPAT OFF)
set(wxUSE_LIBSDL OFF)
set(wxUSE_LIBTIFF OFF)
set(wxUSE_LIBWEBP OFF)
set(wxUSE_MEDIACTRL OFF)
set(wxUSE_PROPGRID OFF)
set(wxUSE_PROTOCOL_FTP OFF)
set(wxUSE_PROTOCOL_HTTP OFF)
set(wxUSE_REGEX OFF)
set(wxUSE_RIBBON OFF)
set(wxUSE_RICHTEXT OFF)
set(wxUSE_SOCKETS OFF)
set(wxUSE_STC OFF)
set(wxUSE_URL OFF)
set(wxUSE_WEBREQUEST OFF)
set(wxUSE_WEBVIEW OFF)
set(wxUSE_WXHTML_HELP OFF)
set(wxUSE_XML OFF)
set(wxUSE_XRC OFF)
set(wxUSE_ZIPSTREAM OFF)
FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.3.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(wxWidgets)

# Plog
FetchContent_Declare(
    plog
    GIT_REPOSITORY https://github.com/SergiusTheBest/plog.git
    GIT_TAG 1.1.11
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(plog)

find_package(OpenCV REQUIRED)

find_package(onnxruntime CONFIG REQUIRED
    PATHS "${CMAKE_CURRENT_LIST_DIR}/thirdparty/ort/install"
    NO_DEFAULT_PATH
)

set(SOURCES
    main.cpp
)

if (WIN32)
    #add_executable(main WIN32 ${SOURCES})
    add_executable(main ${SOURCES})
else()
    add_executable(main ${SOURCES})
endif()

target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(
    main
    PRIVATE
    ${OpenCV_LIBS}
    wx::core wx::base
    onnxruntime::onnxruntime
    plog::plog
)

install(TARGETS main)
install(FILES $<TARGET_RUNTIME_DLLS:main> DESTINATION bin)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "Main")
set(CPACK_PACKAGE_VENDOR "Vendor")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "NSIS")
include(CPack)
