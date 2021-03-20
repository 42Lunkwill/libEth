#include "libEthernet.h"

int main()
{
    testLib();

    libEthernet *com;
    com = new libEthernet("127.0.0.1");
    delete com;
    std::string s("127.0.0.1");
    com = new libEthernet(s);
    delete com;
    
}