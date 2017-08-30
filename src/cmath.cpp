#include <iostream>
#include <libcellml>

int main(int argc, char* argv[])
{
    std::cout << "CellML Math\n(using libCellML " << libcellml::versionString()
              << ")" << std::endl;
    return 0;
}
