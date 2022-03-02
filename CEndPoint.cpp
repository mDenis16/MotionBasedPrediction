
#include "CSensor.h"
#include "CEndPoint.h"

CEndPoint::ptr CEndPoint::get_metadata(int id) const {
    con_list::const_iterator metadata_it = m_connection_list.find(id);
    if (metadata_it == m_connection_list.end()) {
        return CEndPoint::ptr();
    }
    else {
        return metadata_it->second;
    }
}

void CEndPoint::connect(ptr sensor) {
    websocketpp::lib::error_code ec;

    client::connection_ptr con = m_endpoint.get_connection(sensor->compose_uri(), ec);

    if (ec) {
        std::cout << "> Connect initialization error: " << ec.message() << std::endl;
        return;
    }

    sensor->set_id(m_next_id++);
    sensor->SetHdl(con->get_handle());


    m_connection_list[sensor->get_id()] = sensor;


    con->set_message_handler(websocketpp::lib::bind(
        &CSensor::OnMessage,
        sensor,
        websocketpp::lib::placeholders::_1,
        websocketpp::lib::placeholders::_2
    ));

    con->set_open_handler(websocketpp::lib::bind(
        &CSensor::OnOpen,
        sensor,
        &m_endpoint,
        websocketpp::lib::placeholders::_1
    ));
    con->set_fail_handler(websocketpp::lib::bind(
        &CSensor::OnFail,
        sensor,
        &m_endpoint,
        websocketpp::lib::placeholders::_1
    ));
    con->set_close_handler(websocketpp::lib::bind(
        &CSensor::OnClose,
        sensor,
        &m_endpoint,
        websocketpp::lib::placeholders::_1
    ));

    m_endpoint.connect(con);

}

void CEndPoint::close(int id, websocketpp::close::status::value code, std::string reason)
{
    websocketpp::lib::error_code ec;

    con_list::iterator metadata_it = m_connection_list.find(id);
    if (metadata_it == m_connection_list.end()) {
        std::cout << "> No connection found with id " << id << std::endl;
        return;
    }

    m_endpoint.close(metadata_it->second->GetHdl(), code, reason, ec);
    if (ec) {
        std::cout << "> Error initiating close: " << ec.message() << std::endl;
    }
}