#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 

#include <thread>

#include "libEthernet.h"

libEthernet::libEthernet(libEthernet::E_INSTANCE_TYPE instance, const char *ip, int port, libEthernet::E_CONNECTION_TYPE connectionType):
    _instance(instance), _ip(ip), _port(port), _connectionType(connectionType)
{
    _socket_fd = -1;
}

libEthernet::~libEthernet()
{
    if (this->_socket_fd)
        close(this->_socket_fd);
}


libEthernet::E_STATUS libEthernet::serverConfig()
{
    struct sockaddr_in address;
    int opt = 1;
    int newSocket = -1;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->_port); 

    if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR,  &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        return libEthernet::FAILURE;
    }
    if (bind(this->_socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("bind failed"); 
        return libEthernet::FAILURE;
    } 

    if (listen(this->_socket_fd, 3) < 0) 
    { 
        perror("listen"); 
        return libEthernet::FAILURE;
    }
    int addrlen = sizeof(address);
    if ((newSocket = accept(this->_socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    { 
        perror("accept");
        return libEthernet::FAILURE;
    }

    std::thread t(&libEthernet::readMsg, this, newSocket);

    return libEthernet::OK;
}

void libEthernet::readMsg(int fd)
{
    LOG("");
    char buffer[1024] = {0};
    while (1)
    {
        std::cout << "frifir" << std::endl;
        if (recv(fd, buffer, 1024, 0) > 0)
        {
            
            std::cout << "mesg" << std::endl;
            this->notifyMsg(buffer);
        }
    }
}

libEthernet::E_STATUS libEthernet::clientConfig()
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(this->_port); 

    if(inet_pton(AF_INET, this->_ip, &address.sin_addr) <= 0) 
    {
        perror("\nInvalid address/ Address not supported \n");
        return libEthernet::FAILURE;
    }

    if (connect(this->_socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("\nConnection Failed"); 
        return libEthernet::FAILURE;
    }

    std::thread t(&libEthernet::readMsg, this,  this->_socket_fd);
    return libEthernet::OK;
}

libEthernet::E_STATUS libEthernet::initCom()
{
    int type;
    if (this->_connectionType == libEthernet::UDP)
        type = SOCK_DGRAM;
    else
        type = SOCK_STREAM;

    if ((this->_socket_fd = socket(AF_INET, type, 0)) == 0)
    {
        perror("socket failed");
        return libEthernet::FAILURE;
    }

    if (this->_instance == libEthernet::SERVER)
        return this->serverConfig();
    else
        return this->clientConfig();
}

libEthernet::E_STATUS libEthernet::sendMsg(const char *msg) const
{
    if (this->_socket_fd < 0)
    {
        LOG_ERROR("No socket");
        return libEthernet::FAILURE;
    }

    LOG(msg);

    send(this->_socket_fd , msg , strlen(msg) , 0 ); 

    return libEthernet::OK;
}

void libEthernet::addNotifier(libEthernetNotifier *notifier)
{
    this->_notifiers.push_back(notifier);
}

void libEthernet::notifyMsg(const char *msg)
{
    for (auto &i : this->_notifiers)
    {
        i->notifyNewMsg(msg);
    }
}