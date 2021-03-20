#ifndef LIB_ETHERNET_H
#define LIB_ETHERNET_H

#define LOG(x) std::cout << __func__ << ": " << x << std::endl;

#include <string>

class libEthernet
{
public:

    enum E_CONNECTION_TYPE {
        UDP,
        TCP
    };

    enum E_INSTANCE_TYPE {
        CLIENT,
        SERVER
    };

    enum E_STATUS {
        OK,
        FAILURE
    };

    libEthernet(E_INSTANCE_TYPE instance, const char *ip, int port, E_CONNECTION_TYPE connectionType);
    libEthernet(E_INSTANCE_TYPE instance, std::string ip, int port, E_CONNECTION_TYPE connectionType): libEthernet(instance, ip.c_str(), port, connectionType) {}
    ~libEthernet();

    E_STATUS            initCom();
    E_STATUS            serverConfig();
    E_STATUS            clientConfig();

    E_STATUS            sendMsg(const char *msg);
    E_STATUS            sendMsg(std::string s) { return this->sendMsg(s.c_str()); }


private:
    E_INSTANCE_TYPE     _instance;
    const char *        _ip;
    int                 _port;
    E_CONNECTION_TYPE   _connectionType;

    int                 _socket_fd;
};

void testLib();

#endif // LIB_ETHERNET_H