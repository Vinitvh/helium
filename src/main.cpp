#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

enum class TokenType
{
    KEYWORD,
    INT_TYPE,
    SEMICOLON
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(std::string &str)
{
    std::vector<Token> tokens;
    std::string buff;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        // Check first character is alphabet and not number
        if (std::isalpha(c))
        {
            buff.push_back(c);
            i++;
            // Loop until its alphanumeric character
            while (std::isalpha(str.at(i)))
            {
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            if (buff == "return")
            {
                tokens.push_back({.type = TokenType::KEYWORD});
                buff.clear();
                continue;
            }
            else
            {
                std::cerr << "Invalid syntax!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isdigit(c))
        {
            buff.push_back(c);
            i++;
            while (std::isdigit(str.at(i)))
            {
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::INT_TYPE, .value = buff});
            buff.clear();
        }
        else if (c == ';')
        {
            tokens.push_back({.type = TokenType::SEMICOLON});
        }
        else if (isspace(c))
        {
            continue;
        }
        else
        {
            std::cerr << "Invalid syntax!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

std::ostream& operator<<(std::ostream &os, const Token &token)
{
    switch (token.type)
    {
        case TokenType::KEYWORD:
            os << "KEYWORD";
            break;
        case TokenType::INT_TYPE:
            os << "INT(" << token.value.value() << ")";
            break;
        case TokenType::SEMICOLON:
            os << "SEMICOLON";
            break;
    }
    return os;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
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

    std::vector<Token> buf = tokenize(content);
    for(const auto &c : buf) {
        std::cout << c << std::endl;
    }
    return EXIT_SUCCESS;
}