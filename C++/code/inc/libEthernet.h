#ifndef LIB_ETHERNET_H
#define LIB_ETHERNET_H

#include <string>

class libEthernet
{
public:
    libEthernet();
    libEthernet(const char *ip);
    libEthernet(std::string ip): libEthernet(ip.c_str()) {}

    ~libEthernet();
};

void testLib();

#endif // LIB_ETHERNET_H