#ifndef LIB_ETHERNET_H
#define LIB_ETHERNET_H

#define LOG(x) std::cout << __func__ << ": " << x << std::endl;
#define LOG_ERROR(x) LOG(x)

#include <string>
#include <vector>
#include <iostream>

class libEthernetNotifier
{
public:
    virtual ~libEthernetNotifier() {};

    virtual void notifyNewMsg(const char *msg) {std::cout << msg << std::endl; }
};


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

    void                addNotifier(libEthernetNotifier *notifier);

    E_STATUS            initCom();
    E_STATUS            serverConfig();
    E_STATUS            clientConfig();

    E_STATUS            sendMsg(const char *msg) const;
    E_STATUS            sendMsg(std::string s) const { return this->sendMsg(s.c_str()); }


private:
    E_INSTANCE_TYPE     _instance;
    const char *        _ip;
    int                 _port;
    E_CONNECTION_TYPE   _connectionType;

    int                 _socket_fd;

    std::vector<libEthernetNotifier*>    _notifiers;

    void readMsg(int fd);
    void notifyMsg(const char *msg);
};

void testLib();

#endif // LIB_ETHERNET_H