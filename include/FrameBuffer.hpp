#ifndef __FRAMEBUFFER_HPP__
#define __FRAMEBUFFER_HPP__

#include "common.hpp"

class FrameBuffer 
{
private:
    std::queue<cv::Mat> buffer;
    std::mutex mtx;
    std::condition_variable cv;
    size_t maxSize;
    bool isRunning;

public:
    explicit FrameBuffer(size_t maxFrames);
    void pushFrame(const cv::Mat& frame);
    cv::Mat getFrame();
    void stop();
};

#endif