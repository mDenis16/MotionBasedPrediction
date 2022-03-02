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

typedef websocketpp::client<websocketpp::config::asio_client> client;

class CSensor {
public:
    

    CSensor(std::string type)
        : m_status("Connecting")
        , m_type(m_type)
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

    std::string compose_uri() {
        return std::string("");
    }
    int get_id() const {
        return m_id;
    }
    void set_id(int id) {
        m_id = id;
    }

    std::string get_status() const {
        return m_status;
    }

private:
    int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_type;
    std::string m_server;
    std::string m_error_reason;
};

