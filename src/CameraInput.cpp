#include "CameraInput.hpp"

CameraInput::CameraInput(int cameraIndex, FrameBuffer& fb)
	: buffer(fb)
{
	cap.open(cameraIndex);
	if (!cap.isOpened())
	{
		std::cerr << "❌ 카메라를 열 수 없습니다! (Index: " << cameraIndex << ")" << std::endl;
		exit(-1);
	}
}

void CameraInput::start() 
{
	isRunning = true;
	captureThread = std::thread([this] {
			cv::Mat frame;
			while (isRunning) {
				cap >> frame;
				if (frame.empty()) continue;
				buffer.pushFrame(frame);  // 프레임 버퍼에 저장
			}
		});
}

void CameraInput::stop()
{
    isRunning = false;  // ✅ 카메라 입력 종료
    buffer.stop();  // ✅ FrameBuffer 내부 스레드 정리
    if (captureThread.joinable())
        captureThread.join();
    cap.release();
}