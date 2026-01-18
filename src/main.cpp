#include <iostream>
#include <fstream>
#include <sstream>

#include <classes/machine.hpp>
#include <classes/instruction.hpp>

int main(int argc, char** argv) {
    if (!argv[1]) {
        std::cout << "[ \x1b[91mUsage Error\x1b[0m ] Please provide a file name!\n";
        return 1;
    }

    std::ifstream File;

    File.open(argv[1], std::ios::binary);

    if (!File.is_open()) {
        std::cout << "[ \x1b[91mFile Error\x1b[0m ] Failed to open \x1b[91m" << argv[1] << "\x1b[0m!\n";
        return 1;
    }

    Machine MachineI;

    Vec<Byte> Bytecode = Vec<Byte>(
        std::istreambuf_iterator<char>(File),
        std::istreambuf_iterator<char>()
    );

    MachineI.Execute(MachineI.Decode(Bytecode));
}