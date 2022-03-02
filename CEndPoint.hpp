#pragma once
typedef websocketpp::client<websocketpp::config::asio_client> client;
                                     

class CEndPoint {
private:
    std::string m_url;
public:
    typedef websocketpp::lib::shared_ptr<CSensor> ptr;

    CEndPoint() : m_next_id(0) {
        m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
        m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

        m_endpoint.init_asio();
        m_endpoint.start_perpetual();

        m_thread.reset(new websocketpp::lib::thread(&client::run, &m_endpoint));
    }


    ~CEndPoint() {
        m_endpoint.stop_perpetual();

        for (con_list::const_iterator it = m_connection_list.begin(); it != m_connection_list.end(); ++it) {
            if (it->second->get_status() != "Open") {
                // Only close open connections
                continue;
            }

            std::cout << "> Closing connection " << it->second->get_id() << std::endl;

            websocketpp::lib::error_code ec;
            m_endpoint.close(it->second->GetHdl(), websocketpp::close::status::going_away, "", ec);
            if (ec) {
                std::cout << "> Error closing connection " << it->second->get_id() << ": "
                    << ec.message() << std::endl;
            }
        }

        m_thread->join();
    }

    void Connect(ptr sensor);


    void Close(int id, websocketpp::close::status::value code, std::string reason);
    
    void SetUrl(std::string _url) {
        m_url = _url;
    }
    std::string GetUrl() {
        return m_url;
    }
    void message_handle(websocketpp::connection_hdl hdl, client::message_ptr msg) {
        std::cout << "OnMessage called with hdl: " << hdl.lock().get()
            << " and message (" << msg->get_payload().size() << "): " << msg->get_payload()
            << std::endl;

    }
    ptr GetMeta(int id) const;

    typedef std::map<int, ptr> con_list;
private:
    

    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

    con_list m_connection_list;
    int m_next_id;
};
