#include "CSensor.h"


void CSensor::OnOpen(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Open";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
}
void CSensor::OnFail(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Failed";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_error_reason = con->get_ec().message();
}

void CSensor::OnClose(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: " << con->get_remote_close_reason();
    m_error_reason = s.str();
}

void CSensor::OnMessage(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::cout << "ON MESSAGE SOCKET ID   " << m_id << msg->get_payload() << std::endl;

    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        //. m_messages.push_back(msg->get_payload());
    }
    else {
        // m_messages.push_back(websocketpp::utility::to_hex(msg->get_payload()));
    }
}