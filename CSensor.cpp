#include "CSensor.hpp"
#include "CEndPoint.hpp"

#include <nlohmann\json.hpp>
#include <glm\vec3.hpp>

glm::vec3 CSensor::ReadVector() {
    
    if (Value.empty())
        return glm::vec3(0, 0, 0);

    try {
        std::lock_guard<std::mutex> guard(mtx);
        const auto json = nlohmann::json::parse(Value);

        auto samp = json["values"].get<std::vector<float>>();

        auto vec = glm::vec3(samp.at(0), samp.at(1), samp.at(2));
        return vec;

    }
    catch (int ex) {
        return glm::vec3(0, 0, 0);
    }
  
     
}

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

std::string CSensor::ComposeUri(CEndPoint& endpoint) {
    return endpoint.GetUrl().append(m_type);
}

void CSensor::OnMessage(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    
    std::lock_guard<std::mutex> guard(mtx);

    Value = msg->get_payload();

    //if (msg->get_opcode() == websocketpp::frame::opcode::text) {
    //    //. m_messages.push_back(msg->get_payload());
    //}
    //else {
    //    // m_messages.push_back(websocketpp::utility::to_hex(msg->get_payload()));
    //}
}