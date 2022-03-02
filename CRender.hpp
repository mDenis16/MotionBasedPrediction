#pragma once
#include <raylib.h>
#include <thread>

class CRender
{
private:
	int screenWidth, screenHeight = 0;
	bool bInitialized = false;

	std::thread tRenderThread;
	Camera3D Camera;
public:
	void RenderScene();
	void Initialize(int _w, int _h);
	void CameraSetup();
	void Run();
	Camera3D& GetCam() { return Camera; }
};

