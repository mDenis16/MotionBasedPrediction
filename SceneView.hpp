#pragma once

#include <thread>



class SceneView
{
public:
	void Init();

	glm::vec3 localPosition = glm::vec3(0,0,0);
	float localHeading = 0.f;


	std::thread* renderThread;
	void OnRender();

	glm::vec3 acceleration;

	websocketpp::lib::shared_ptr<CSensor> AccelerationSensor;

	CEndPoint sensors;

};
inline SceneView scene;
