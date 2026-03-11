#include <iostream>
#include <onnxruntime_cxx_api.h>

int main(int args, char **argv) {
    std::cout << "ONNX Runtime version: " << Ort::GetVersionString() << std::endl;
    return 0;
}
