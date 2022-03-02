#pragma once
#include <raylib.h>
#include <thread>


class CRender
{
private:
	int screenWidth, screenHeight = 0;
	bool bInitialized = false;

	std::thread tRenderThread;
	Camera CCamera = { 0 };
public:
	void RenderScene();
	void Initialize(int _w, int _h, CPrediction* pred);
	void CameraSetup();
	void Run();

	CPrediction* Pred;

	Camera& GetCam() { return CCamera; }
};

