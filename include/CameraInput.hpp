#ifndef __CAMERAINPUT_HPP__
#define __CAMERAINPUT_HPP__

#include "common.hpp"
#include "FrameBuffer.hpp"

class CameraInput {
private:
    bool isRunning = false;
    cv::VideoCapture cap;
    std::thread captureThread;
    FrameBuffer& buffer;

public:
    CameraInput(int cameraIndex, FrameBuffer& fb);
    void start();
    void stop();
};

#endif