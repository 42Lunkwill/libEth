#include "libEthernet.h"

int main()
{
    testLib();

    libEthernet *com, *com2;
    com = new libEthernet(libEthernet::SERVER, "127.0.0.1", 8080, libEthernet::UDP);
    //com->initCom();

    std::string s("127.0.0.1");
    com2 = new libEthernet(libEthernet::CLIENT, s, 8080, libEthernet::TCP);
    com2->initCom();
    com2->sendMsg("test 1");
    delete com;
    delete com2;
}