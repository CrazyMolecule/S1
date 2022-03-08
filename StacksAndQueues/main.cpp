#include <iostream>
#include <fstream>
#include <string>

#include "Queue.h"
#include "Stack.h"
#include "Converter.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    
    std::istream* input;
    std::ifstream fileInput;

    // Open file or read from console
    if (argc == 1)
    {
        input = &std::cin;
    }
    else
    {
        std::string filename = argv[1];
        fileInput.open(filename);
        input = &fileInput;

        if (!fileInput.is_open())
        {
            std::cerr << "Ошибка: Файл ввода не открыт!";
            return -1;
        }
    }

    // Convert file lines from infix to postfix
    stack<long long> output;
    std::string line = "";
    try
    {
        while (getline(*input, line))
        {
            if (line.empty())
                continue;

            Converter convertible(line);
            output.push(convertible.toPostfix().calculate());
        }
    }
    catch (const char* exeption)
    {
        std::cerr << "Ошибка: " << exeption << std::endl;
        return -1;
    }


    fileInput.close();

    return 0;
}