#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect usage. Correct usage is ..." << std::endl;
        std::cerr << "helium <input.hl> " << std::endl;
        return EXIT_FAILURE;
    }

    // Buffer to store file contents
    std::stringstream buffer;
    // Read from the file
    std::fstream input(argv[1], std::ios::in);
    buffer << input.rdbuf();
    // Convert buffer to string
    std::string content = buffer.str();
    input.close();

    std::cout << content << std::endl;

    return EXIT_SUCCESS;
}