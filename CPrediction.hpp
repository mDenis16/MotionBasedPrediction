#pragma once
class CPrediction
{
public:
	typedef websocketpp::lib::shared_ptr<CSensor> sensor_ptr;

	sensor_ptr Accelerometer;


	void InitializeSensors(CEndPoint& endpoint);

};

