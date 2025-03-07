#include "VirtualCamera.hpp"

VirtualCamera::VirtualCamera(FrameBuffer& fb) 
	: buffer(fb) {}

void VirtualCamera::start()
{
	isRunning = true;
}

void VirtualCamera::processFrames()
{
	while (isRunning)
	{
		cv::Mat frame = buffer.getFrame();
		if (frame.empty()) continue;

		int key = cv::waitKey(30);
		if (key == 27)
		{
    		std::cout << "ESC 키가 눌렸습니다. 종료합니다!" << std::endl;
			isRunning = false;
			break;
		}
		else if (key == 49)
		{
			option ^= 1;
			std::cout << "* Option - flipping : " << ((option & 0x01) ? "ON *" : "OFF *") << '\n';
		}

		if (option & 0x01)
			option_flip(frame);

		cv::imshow("Virtual Camera Output", frame);
	}
}

void VirtualCamera::stop()
{
	isRunning = false;
}

void VirtualCamera::option_flip(cv::Mat &frame)
{
	// ✅ 0.2초마다 flipState 변경
	auto now = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFlipTime).count() >= 100) {
		flipState = !flipState;  // 반전 상태 토글
		lastFlipTime = now;
	}

	// ✅ 좌우 반전 적용 (flipState가 true일 때만 적용)
	if (flipState) {
		cv::flip(frame, frame, 1);  // 1: 좌우 반전
	}

	// ✅ 이미지 중앙에 세로 구분선 추가 (흰색 선)
	int centerX = frame.cols / 2;  // 정중앙 X좌표
	cv::line(frame, cv::Point(centerX, 0), cv::Point(centerX, frame.rows), cv::Scalar(255, 255, 255), 2);
}