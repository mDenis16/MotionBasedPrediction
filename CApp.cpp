#include "CSensor.hpp"
#include "CEndPoint.hpp"
#include "CRender.hpp"
#include "CPrediction.hpp"

#include "CApp.hpp"

void CApp::Run() {


	endpoint.SetUrl("ws://192.168.88.235:8081");

	prediction.InitializeSensors(endpoint);

	render.Initialize(800, 600);


	render.Run();

}