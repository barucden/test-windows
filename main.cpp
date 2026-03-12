#include <iostream>

#include <onnxruntime_cxx_api.h>
#include <opencv2/core.hpp>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>
#include <wx/init.h>
#include <wx/utils.h>

#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    plog::init(plog::debug, "Hello.txt");

    wxInitialize();

    PLOGI << "ONNX Runtime version: " << Ort::GetVersionString() << std::endl;

    const auto wxVersion = wxGetLibraryVersionInfo();
    PLOGI << "wxWidgets version: " << wxVersion.GetVersionString() << std::endl;

    PLOGI << "OpenCV version: " << CV_VERSION << std::endl;

    return 0;
}

