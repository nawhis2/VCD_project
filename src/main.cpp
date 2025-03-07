#include "common.hpp"
#include "FrameBuffer.hpp"
#include "CameraInput.hpp"
#include "VirtualCamera.hpp"

int main() 
{
	FrameBuffer buffer(100);

	CameraInput camera(1, buffer);
	VirtualCamera vcam(buffer);

	std::cout << "---[LOG : 🎬 starting VCD Camera.]" << std::endl;
	camera.start();
	vcam.start();

    std::cout << "---[LOG : 🎥 Execution VCD Camera. (press ESC to exit)]" << std::endl;
	vcam.processFrames();

	camera.stop();
	vcam.stop();
	std::cout << "---[LOG : 🔚 Exit VCD Camera.]" << std::endl;

	return 0;
}