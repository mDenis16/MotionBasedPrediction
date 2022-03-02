#include "CSensor.hpp"
#include "CEndPoint.hpp"
#include "CPrediction.hpp"

void CPrediction::InitializeSensors(CEndPoint& endpoint) {

	LinearAcceleration = sensor_ptr(new CSensor("/sensor/connect?type=android.sensor.linear_acceleration"));
	Accelerometer = sensor_ptr(new CSensor("/sensor/connect?type=android.sensor.accelerometer"));
    RotationGame = sensor_ptr(new CSensor("/sensor/connect?type=android.sensor.game_rotation_vector"));


		
	endpoint.Connect(Accelerometer);
	endpoint.Connect(LinearAcceleration);
	endpoint.Connect(RotationGame);
}

