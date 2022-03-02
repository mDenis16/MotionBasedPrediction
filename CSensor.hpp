#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <glm/vec3.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class CEndPoint;

template <typename T>
constexpr bool IsVector() { return std::is_same<T, glm::vec3>::value; }


class CSensor {
public:
    

    CSensor(std::string type)
        : m_status("Connecting")
        , m_type(type)
        , m_server("N/A") {
    }

    void OnOpen(client* c, websocketpp::connection_hdl hdl);

    void OnMessage(websocketpp::connection_hdl hdl, client::message_ptr msg);

    void OnFail(client* c, websocketpp::connection_hdl hdl);


    void OnClose(client* c, websocketpp::connection_hdl hdl);

    void SetHdl(websocketpp::connection_hdl _hdl) {
        m_hdl = _hdl;
    }


    websocketpp::connection_hdl GetHdl() const {
        return m_hdl;
    }

    std::string ComposeUri(CEndPoint& endpoint);

    int get_id() const {
        return m_id;
    }
    void set_id(int id) {
        m_id = id;
    }

    std::string get_status() const {
        return m_status;
    }

    std::string Value;

    std::mutex mtx;
   
    glm::vec3 ReadVector();


private:

    int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_type;
    std::string m_server;
    std::string m_error_reason;
};

