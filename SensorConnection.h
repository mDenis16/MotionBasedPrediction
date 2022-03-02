#pragma once
class SensorConnection
{
public:

	
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

	websocketpp::connection_hdl m_hdl;
};

