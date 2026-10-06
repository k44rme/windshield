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
      std::cerr << "\nError: Failed to open requested file\nFile: " << file_name << std::endl;
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
            if (next[next.size()-1] == '{')
            {
              next[next.size()-1] = ';';
            }
            else if (next[next.size()-1] == ')') {
              next.push_back(';');
            }
            current.declaration = next;
          } else {
            throw std::runtime_error("\nError: Failed to find the function declaration in "+file_name);
          }

          functions.push_back(current);
        }
        else std::cout << "\nError: " << file_name << "has incorect structure" << std::endl;
      }
      else {
        std::cout << "\nError: " << file_name << "is empty" << std::endl;
      }
    }

  }

  return functions;
}

void new_header(FuncDec obj, std::string definition)
{
  std::ofstream header(obj.destination);
  if (!header) {
    std::cout << "\nError: Requested destination is invalid.\nDestination: " << obj.destination << std::endl;
    exit(EXIT_FAILURE);
  }
  header << "#pragam once\n\n#ifndef " << definition << "\n#define " << definition << "\n\n// #ws declarations\n";
  header << obj.declaration;
  header << "// #ws declaration end";
  header << "\n\n#endif // " << definition << "\n";
}

void append_header(FuncDec obj)
{
  std::vector<std::string> lines;

  {
    std::ifstream file(obj.destination);
    if (!file)
    {
      std::cerr << "\nError: Failed to find a header";
      exit(EXIT_FAILURE);
    } else {
      std::string line;

      while(std::getline(file, line))
      {
        lines.push_back(line);
      }
    }
  }

  std::size_t start_span = lines.size(), end_span = lines.size();

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

  lines.insert(lines.begin() + end_span, obj.declaration);

  std::ofstream out(obj.destination, std::ios::trunc);
  if (out) {
    for (auto current : lines)
    {
      out << current << "\n";
    }
  }
}

