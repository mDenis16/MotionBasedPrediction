#include <raylib.h>

#include <functional>
#include <iostream>
#include <glm\glm.hpp>



#include "pch.h"
#include "sensor.h"
#include "CEndPoint.h"

#include "SceneView.hpp"



static const int INTERPOLATION_TIME_MS = 300;


void SceneView::Init()
{

	//this->AccelerationSensor = std::make_shared< websocketpp::lib::shared_ptr<CSensor>>("alo");

	this->renderThread = new std::thread(std::bind(&SceneView::OnRender, this));


}
static float angleBetween(
	glm::vec3 a,
	glm::vec3 b,
	glm::vec3 origin
) {
	glm::vec3 da = glm::normalize(a - origin);
	glm::vec3 db = glm::normalize(b - origin);
	return glm::acos(glm::dot(da, db));
}
#define MAX_COLUMNS 20

static float game_time_ms_ = 0.f;
float LerpDegrees(float start, float end, float amount) {
	float difference = std::abs(end - start);
	if (difference > 180) {
		// We need to add on to one of the values.
		if (end > start) {
			// We'll add it on to start...
			start += 360;
		}
		else {
			// Add it on to end.
			end += 360;
		}
	}

	// Interpolate it.
	float value = (start + ((end - start) * amount));

	// Wrap it..
	float rangeZero = 360;

	if (value >= 0 && value <= 360)
		return value;

	return fmod(value, rangeZero);
}
struct TextView2D
{
	std::string str;
	glm::vec3 position;
};

uint64_t get_interpolation_time_point_ms() {
	uint64_t time_point = 0;

	if (game_time_ms_ > INTERPOLATION_TIME_MS)
		time_point = game_time_ms_ - INTERPOLATION_TIME_MS;

	return time_point;
}

static const float Unlerp(const double fStart, const double fPos, const double fEnd)
{
	// Avoid dividing by 0 (results in INF values)
	if (fStart == fEnd) return 1.0f;

	return (float)((fPos - fStart) / (fEnd - fStart));
}
double get_time_fraction(uint64_t start_ms, uint64_t stop_ms, uint64_t between_ms) {
	return static_cast<double>(between_ms - start_ms) / static_cast<double>(stop_ms - start_ms);
}



float LOW_LIMIT = 0.0167f;          // Keep At/Below 60fps
float HIGH_LIMIT = 0.1f;            // Keep At/Above 10fps
void SceneView::OnRender()
{
	//--------------------------------------------------------------------------------------


	const int screenWidth = 800;
	const int screenHeight = 800;
	glm::vec3 gtaMins = glm::vec3(-5395.54, -5024.13, 0);
	glm::vec3 gtaMaxs = glm::vec3(5395.54, 9024.13, 0);

	auto center = (gtaMins + gtaMaxs) * 0.5f;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera3D camera = { 0 };
	//-763.4022, 7.327758, 40.59016
	camera.position = Vector3{ 10.0f, 30.0f, 10.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	//auto gridvIew = new Grid<int>(glm::vec3(-250, -250, 0), glm::vec3(250, 250, 0), glm::vec3(30, 30, 0));

	SetCameraMode(camera, CAMERA_FREE); // Set a first person camera mode

	SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	
	// Main game loop
	while (!WindowShouldClose())                // Detect window close button or ESC key
	{
	
		std::vector< TextView2D > Texts;



	

		camera.position = Vector3{ scene.localPosition.x ,scene.localPosition.z + 5, scene.localPosition.y };

		camera.target = Vector3{ scene.localPosition.x ,scene.localPosition.z, scene.localPosition.y };

		


		UpdateCamera(&camera);                  // Update camera

		BeginDrawing();

		ClearBackground(WHITE);

		BeginMode3D(camera);

		DrawGrid(20, 2);

		static int HeadingSpeed = 100;

		static float TargetHeading = 0.f;
		static float LastHeading = 0.f;
		static std::uint32_t lastChange = 0.f;
		float Speed = 0.006f ;

		float cameraAngle = angleBetween(glm::vec3(camera.position.x, camera.position.z, camera.position.y), scene.localPosition, glm::vec3(0, 0, 0));

		bool move = false;
		if (IsKeyDown(KEY_RIGHT)) {
			TargetHeading = -90.f;
			move = true;
		}
		if (IsKeyDown(KEY_LEFT)) {
			TargetHeading = 90.f;
			move = true;
		}
		if (IsKeyDown(KEY_UP)) {
			TargetHeading = 180;
			move = true;
		}
		if (IsKeyDown(KEY_DOWN)) {
			TargetHeading = 360;
			move = true;
		}
	
		 

		localHeading = LerpDegrees(localHeading, TargetHeading, 0.025f);

		
		float radius = 5.f;
		float a = glm::radians(localHeading);

		glm::vec3 location(radius * cos(a) + scene.localPosition.x, radius * sin(a) + scene.localPosition.y, scene.localPosition.z);

		DrawLine3D(Vector3{ scene.localPosition.x, scene.localPosition.z, scene.localPosition.y }, Vector3{ location.x, location.z, location.y }, Color(255, 0, 0, 255));
		if (move)
		{
			double a = glm::radians(localHeading);

		
			glm::vec3 dir(cos(a) ,  sin(a), 0);


			localPosition += dir * Speed;
			
		}




		//DrawPlane(Vector3{ 0, 0, 0 }, Vector2{ 500, 500 }, BLUE);
		
		DrawCylinderWires(Vector3{ localPosition.x, 	localPosition.z, 	localPosition.y }, 2.0f, 2.0f, 4.0f, 6, BLACK);

		EndMode3D();

		

		EndDrawing();
		
		
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseRayWindow();        // Close window and OpenGL context
	//------------------------------------------------------------
}