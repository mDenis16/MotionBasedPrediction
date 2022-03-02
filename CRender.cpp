#include "CRender.hpp"
#include <functional>

void CRender::RenderScene() {
   
    BeginMode3D(Camera);

    DrawGrid(10, 1.0f);

    EndMode3D();


    DrawRayText("Free camera default controls:", 20, 20, 10, BLACK);
}

void CRender::Initialize(int _w, int _h)  {
    
    screenHeight = _h;
    screenWidth = _w;


    InitWindow(screenWidth, screenHeight, "CRender");

    bInitialized = true;

    CameraSetup();

    /*tRenderThread = std::thread(std::bind(&CRender::FFLock, this));
    tRenderThread.detach();*/              // raylib must run on main thread
}



void CRender::CameraSetup() {
    auto& camera = GetCam();

    camera.position = (Vector3)( 10.0f, 10.0f, 10.0f ); // Camera position
    camera.target = (Vector3)( 0.0f, 0.0f, 0.0f );      // Camera looking at point
    camera.up = (Vector3)( 0.0f, 1.0f, 0.0f );          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    SetCameraMode(camera, CAMERA_FREE);
}

void CRender::Run() {

    while (!WindowShouldClose()) {
        UpdateCamera(&Camera);
        ClearBackground(RAYWHITE);
        BeginDrawing();
        RenderScene();
        EndDrawing();
    }

    CloseRayWindow();
}
