#include "CSensor.hpp"
#include "CEndPoint.hpp"
#include "CPrediction.hpp"
#include "CRender.hpp"

#include <functional>
#include <glm\vec3.hpp>
#include  <raylib.h>


Vector3 cubeSize = { 1.0f, 1.0f, 1.0f };

glm::vec3 cubePosition = glm::vec3(0, 0, 0);

float gravity[3] = {0};

void CRender::RenderScene() {
   
    auto vec = Pred->Accelerometer->ReadVector();
    auto linear = Pred->LinearAcceleration->ReadVector();
    auto rotation = Pred->RotationGame->ReadVector();


    std::stringstream ss;
                                                                      //ws://192.168.88.235:8081/sensor/connect?type=android.sensor.game_rotation_vector
   


     float alpha = 0.8;

    // Isolate the force of gravity with the low-pass filter.
    gravity[0] = alpha * gravity[0] + (1 - alpha) * linear.x;
    gravity[1] = alpha * gravity[1] + (1 - alpha) * linear.y;
    gravity[2] = alpha * gravity[2] + (1 - alpha) * linear.z;

    // Remove the gravity contribution with the high-pass filter.
   linear.x -= gravity[0];
    linear.y -= gravity[1];
    linear.z -=  gravity[2];

    
    cubePosition += (linear ) * 0.01f;
    ss << "x: " << linear.x << " y " << linear.y << " z " << linear.z << std::endl;

    BeginMode3D(CCamera);

    DrawCube({ cubePosition.x, cubePosition.z, cubePosition.y }, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);

    DrawGrid(10, 1.0f);

    EndMode3D();

    DrawRayText(ss.str().c_str(), 240, 10, 20, DARKGRAY);


    DrawRayText(ss.str().c_str(), 20, 20, 10, BLACK);
  
}

void CRender::Initialize(int _w, int _h, CPrediction* pred)  {
    
    screenHeight = _h;
    screenWidth = _w;

    Pred = pred;

    InitWindow(screenWidth, screenHeight, "CRender");

    bInitialized = true;

    CameraSetup();

    SetTargetFPS(60);

    /*tRenderThread = std::thread(std::bind(&CRender::FFLock, this));
    tRenderThread.detach();*/              // raylib must run on main thread
}



void CRender::CameraSetup() {

    CCamera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
    CCamera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    CCamera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    CCamera.fovy = 45.0f;                                // Camera field-of-view Y
    CCamera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    SetCameraMode(CCamera, CAMERA_FREE);
}

void CRender::Run() {
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&CCamera);          // Update camera


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

     
        RenderScene();


        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}
