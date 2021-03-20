#include "libEthernet.h"

#include <iostream>

class customNotifier: public libEthernetNotifier
{
public:
    customNotifier() {}
    ~customNotifier() {}

    void notifyNewMsg(const char *msg)
    { 
        std::cout << "new message"  << std::endl;
    }   

};

int main()
{
    libEthernet *com;
    libEthernetNotifier n = libEthernetNotifier();
    customNotifier c = customNotifier();

    com = new libEthernet(libEthernet::SERVER, "127.0.0.1", 8080, libEthernet::TCP);
    com->addNotifier(&n);
    com->addNotifier(&c);
    if (com->initCom() == libEthernet::FAILURE)
        return -1;

    while (1)
    {
    }

    delete com;
}