#include <iostream>
#include <fstream>
#include <string>

#include "Queue.h"
#include "Stack.h"
#include "Converter.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    
    stack <int> Stackeroo;
    Stackeroo.push(2);
    Stackeroo.push(3);
    Stackeroo.push(6);
    Stackeroo.push(7);
    Stackeroo.push(9);
    std::cout << Stackeroo << std::endl;
    Stackeroo.pop();
    std::cout << Stackeroo << std::endl;
    Stackeroo.pop();
    std::cout << Stackeroo << std::endl;
    Stackeroo.pop();
    std::cout << Stackeroo << std::endl;
    Stackeroo.pop();
    std::cout << Stackeroo << std::endl;
    Stackeroo.pop();
    std::cout << Stackeroo << std::endl;

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

            line = "(3 + 5) / 5 - 8 * 3 + (8 * 30 + 10 * (7 * 2 - 10) * 30)";
            Converter convertible(line);
            long long postfixLine = convertible.toPostfix().calculate();
            output.push(postfixLine);

            std::cout << postfixLine;
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
    }

    fileInput.close();

    return 0;
}