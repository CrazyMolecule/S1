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
            long long postfixLine = convertible.toPostfix().calculate();
            output.push(postfixLine);
        }
    }
    catch (const char* exception)
    {
        std::cerr << exception << std::endl;
        return -1;
    }

    // Input
    while (!output.isEmpty())
    {
        std::cout << output.pop();

        if (!output.isEmpty())
            std::cout << ' ';
    }

    fileInput.close();

    return 0;
}