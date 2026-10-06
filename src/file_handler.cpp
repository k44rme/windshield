#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/file_handler.h"

std::vector<FuncDec> function_declaration(const std::string &file_name) {
  const std::string file(std::filesystem::absolute(file_name));
  std::vector<FuncDec> functions = {};
  {
    std::ifstream f;
    f.open(file);

    if (!f) {
      std::cerr << "\nError: Failed to open requested file\nFile: " << file_name
                << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string s;
    while (std::getline(f, s)) {
      std::string dest;
      if (s.find("// #ws ") == 0) {
        std::string temp = "// #ws ";
        dest = s.substr(temp.size());

        FuncDec current;
        current.destination = dest;

        std::string next;
        if (std::getline(f, next)) {
          if (next.back() == '{') {
            next.back() = ';';
          } else if (next.back() == ')') {
            next.push_back(';');
          }
          current.declaration = next;
        } else {
          throw std::runtime_error(
              "\nError: Failed to find the function declarations in " +
              file_name);
        }

        functions.push_back(current);
        continue;
      }
    }
    return functions;
  }
}

void new_header(FuncDec &obj, std::string definition) {
  if (definition.empty()) {
    std::runtime_error("\nError: Failed to generate definiton");
  }

  std::ofstream header(obj.destination, std::ios::out | std::ios::trunc);

  if (!header) {
    std::runtime_error(
        "\nError: Requested destination is invalid.\nDestination: " +
        obj.destination);
  }
  header << "#pragma once\n\n"
         << "#ifndef " << definition << "\n"
         << "#define " << definition << "\n\n"
         << "// #ws declarations start\n\n"
         << obj.declaration;
  if (!obj.declaration.empty() && obj.declaration.back() != '\n')
    header << '\n';
  header << "\n// #ws declarations end\n\n"

         << "#endif // " << definition << "\n";

  header.flush();
}

void append_header(FuncDec &obj) {
  std::vector<std::string> lines;

  //  std::vector<std::string> config = read_config();
  //  std::string include;
  //  for (size_t i = 0; i < config.size(); i++) {
  //    if (config[i].find("include_path")) {
  //      std::string temp = "include_path = ";
  //      include = config[i].substr(temp.size());
  //    }
  //  }

  {
    std::ifstream file(obj.destination);
    if (!file) {
      std::cerr << "\nError: Failed to find a header";
      exit(EXIT_FAILURE);
    } else {
      std::string line;

      while (std::getline(file, line)) {
        lines.push_back(line);
      }
    }
  }

  std::size_t start_span = 0, end_span = 0;

  for (std::size_t i; i < lines.size(); i++) {
    start_span = lines.at(i).find("// #ws declarations start");
    end_span = lines.at(i).find("// #ws declarations end");
  }

  if (start_span == 0 || end_span == 0) {
    std::cout << "failed" << std::endl;
    std::cout
        << "\nError: Failed to find 'declaration section', which should "
           "contains '// #ws declarations start' and '// #ws declarations end' "
           "strings!"
        << std::endl;
    exit(EXIT_FAILURE);
  }
  lines.insert(lines.begin() + end_span, obj.declaration);

  {
    std::ofstream out(obj.destination, std::ios::trunc);
    if (out) {
      for (auto current : lines) {
        out << current << "\n";
      }
    }
  }
}

std::vector<std::string> read_config() {
  std::vector<std::string> strings = {};
  {
    std::string path = std::filesystem::absolute("windshield.txt");
    std::ifstream config(path);

    if (!config) {
      std::cout << "failed" << std::endl;
      std::cout << "\nError: Failed to find Windshield config!\nType "
                   "'windshield init' command to init windshield."
                << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string s;
    while (std::getline(config, s)) {
      if (!s.empty()) {
        strings.push_back(s);
      }
    }
  }
  return strings;
}
