#ifndef __VIRTUALCAMERA_HPP__
#define __VIRTUALCAMERA_HPP__

#include "common.hpp"
#include "FrameBuffer.hpp"

class VirtualCamera {
private:
    FrameBuffer& buffer;
    bool isRunning = false;
    bool flipState = false;  // ✅ 현재 반전 상태
    std::chrono::steady_clock::time_point lastFlipTime;
    int option = 0;

public:
    explicit VirtualCamera(FrameBuffer& fb);
    void start();
	void processFrames();
    void stop();

    void option_flip(cv::Mat &frame);
};

#endif