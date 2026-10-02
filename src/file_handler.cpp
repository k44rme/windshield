#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "file_handler.h"

std::vector<FuncDec> function_declaration(const std::string& file_name)
{
  const std::string file(std::filesystem::absolute(file_name));
  std::vector<FuncDec> functions = {};
  {
    std::ifstream f;
    f.open(file);

    if(!f)
    {
      std::cerr << "Failed to open file: " << file_name << std::endl;
      exit(EXIT_FAILURE);
    }
    
    std::string s;
    while(std::getline(f, s))
    {
      if (s.empty()) continue;
      if (!s.empty() && s[0] == '/')
      {
        if (s[1] == '/' && s[2] == ' ')
        {
          std::string temp = "// #ws ";
          std::string dest = s.substr(temp.size());

          FuncDec current;
          current.destination = dest;
          
          std::string next;
          if (std::getline(f, next)) {
            current.declaration = next;
          } else {
            throw std::runtime_error(file_name+": Failed to find the function declaration");
          }

          functions.push_back(current);
        }
        else std::cout << file_name << ": Incorrect file structure!" << std::endl;
      }
      else {
        std::cout << file_name << ": File is empty" << std::endl;
      }
    }

  }

  return functions;
}

void new_header(std::string destination, std::string content, std::string definition)
{
  std::ofstream header(destination);
  header << "#pragam once\n\n#ifndef " << definition << "\n#define " << definition << "\n\n// #ws declarations\n";
  header << content;
  header << "// #ws declaration end";
  header << "\n\n#endif // " << definition << "\n";
}

void append_header(std::string destination, std::string content)
{
  std::vector<std::string> lines;

  {
    std::ifstream file(destination);
    if (!file)
    {
      std::cerr << "Failed to find a header";
      exit(EXIT_FAILURE);
    } else {
      std::string line;

      while(std::getline(file, line))
      {
        lines.push_back(line);
      }
    }
  }

  std::size_t start_span, end_span = lines.size();

  for (std::size_t i; i <= lines.size()-1; i++)
  {
    if (lines.at(i) == "// #ws declaration")
    {
      start_span = i;
    } else if (lines.at(i) == "// #ws declaration end")
    {
      end_span = i;
      break;
    }
  }

  lines.insert(lines.begin() + end_span, content);

  std::ofstream out(destination, std::ios::trunc);
  if (out) {
    for (auto current : lines)
    {
      out << current << "\n";
    }
  }
}

