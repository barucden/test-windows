#include <iostream>

#include <onnxruntime_cxx_api.h>
#include <opencv2/core.hpp>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>
#include <wx/utils.h>

int main(int args, char **argv) {
    plog::init(plog::debug, "Hello.txt");

    std::cout << "ONNX Runtime version: " << Ort::GetVersionString() << std::endl;

    const auto wxVersion = wxGetLibraryVersionInfo();
    std::cout << "wxWidgets version: " << wxVersion.GetVersionString() << std::endl;

    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    return 0;
}

