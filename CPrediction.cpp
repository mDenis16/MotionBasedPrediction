#include "CSensor.hpp"
#include "CEndPoint.hpp"
#include "CPrediction.hpp"

void CPrediction::InitializeSensors(CEndPoint& endpoint) {

	Accelerometer = sensor_ptr(new CSensor("/sensor/connect?type=android.sensor.accelerometer"));

	endpoint.Connect(Accelerometer);

}
