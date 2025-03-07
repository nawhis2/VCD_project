#include "FrameBuffer.hpp"
#include "CameraInput.hpp"

FrameBuffer::FrameBuffer(size_t maxFrames) 
	: maxSize(maxFrames), isRunning(true) {}

void FrameBuffer::pushFrame(const cv::Mat& frame) 
{
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] { return buffer.size() < maxSize || !isRunning; });

	if (!isRunning)
		return ;

	buffer.push(frame.clone());  // 프레임을 복사해서 저장
	cv.notify_all();
}

cv::Mat FrameBuffer::getFrame() 
{
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] { return !buffer.empty() || !isRunning; });

	if (!isRunning)
		return cv::Mat();

	cv::Mat frame = buffer.front();
	buffer.pop();
	cv.notify_all();
	return frame;
}

void FrameBuffer::stop()
{
	std::unique_lock<std::mutex> lock(mtx);
	isRunning = false;
	cv.notify_all();  // ✅ 대기 중인 스레드를 깨워서 즉시 종료하도록 유도
}