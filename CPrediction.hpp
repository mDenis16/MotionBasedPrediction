#pragma once
class CPrediction
{
public:
	typedef websocketpp::lib::shared_ptr<CSensor> sensor_ptr;

	sensor_ptr Accelerometer;
	sensor_ptr LinearAcceleration;
	sensor_ptr RotationGame;


	void InitializeSensors(CEndPoint& endpoint);

};

