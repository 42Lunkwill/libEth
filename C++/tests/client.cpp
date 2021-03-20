#include "libEthernet.h"

#include <iostream>

int main()
{
    libEthernet *com;

    std::string s("127.0.0.1");
    com = new libEthernet(libEthernet::CLIENT, s, 8080, libEthernet::TCP);
    if (com->initCom() == libEthernet::FAILURE)
        return -1;

    std::string msg;
    while(1)
    {
        std::cin >> msg;
        com->sendMsg(msg);
    }

    delete com;
}