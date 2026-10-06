#include <vector>
#include <string>
#include <filesystem>
#include <cctype>
#include <iostream>

#include "cli_basic.h"
#include "file_handler.h"

std::string generate_defininition(std::string& str)
{
  for (size_t i = 0; i < str.size()-1; i++) {
    if (str[i] == '-') {
      str[i] = '_';
    }
    else if (str[i] == '.') {
      break;
    }
    else {
      if (!isupper(str[i])) {
        str[i] = toupper(str[i]);
      }
    }
  }

  str.push_back('_');
  str.push_back('H');

  return str;
}

void gen(const std::string& file_name)
{
  std::cout << "Starting to read recived file ... ";
  std::vector<FuncDec> functions = function_declaration(file_name);
  std::string name = file_name;

  std::cout << "done" << std::endl;
  
  std::cout << "Writing data ... ";
  for (std::size_t i = 0; i < functions.size()-1; i++) {
    if (std::filesystem::exists(functions[i].destination)) {
      append_header(functions[i]);
    } else {
      new_header(functions[i], generate_defininition(name));
    }
  }
  std::cout << "done" << std::endl;
}

void version()
{
  std::cout << "Windshield 1.0.0\nCreated by k44rme\nRespository: https://github.com/k44rme/windshield" << std::endl;
}
