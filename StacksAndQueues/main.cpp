#include <iostream>
#include <fstream>
#include <string>

#include "Queue.h"
#include "Stack.h"
#include "Converter.h"

using namespace bavykin;

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "ru");

  std::istream* input;
  std::ifstream fileInput;

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
      std::cerr << "Error: the input file was not opened!";
      return 1;
    }
  }

  stack<long long> output;
  std::string line = "";
  try
  {
    while (getline(*input, line))
    {
      if (line.empty())
      {
        continue;
      }

      Converter convertible(line);
      long long postfixLine = convertible.toPostfix().calculate();
      output.push(postfixLine);
    }
  }
  catch (std::logic_error& exception)
  {
    std::cerr << "Logic error! " << exception.what() << std::endl;
    return 2;
  }
  catch (std::overflow_error& exception)
  {
    std::cerr << "Overflow error! " << exception.what() << std::endl;
    return 2;
  }

  while (!output.isEmpty())
  {
    std::cout << output.pop();

    if (!output.isEmpty())
    {
      std::cout << ' ';
    }
  }

  fileInput.close();

  return 0;
}
